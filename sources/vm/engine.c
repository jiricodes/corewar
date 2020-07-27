/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 17:08:32 by jnovotny          #+#    #+#             */
/*   Updated: 2020/07/27 18:59:35 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "oplist_cw.h"

int	if_op(int8_t byte)
{
	int cnt;
	cnt = 0;
	while (cnt < 16)
	{
		if (byte == g_oplist[cnt].opcode)
			return (g_oplist[cnt].opcode - 1);
		cnt += 1;
	}
	return (-1);
}

static void check_operation(t_vm *core, t_car *car)
{
	car->op_index = if_op(core->arena[car->pc]);
	if (car->op_index != -1)
	{
		car->cooldown = g_oplist[car->op_index].exec_cycles;
		ft_bzero(car->args, sizeof(t_args));
	}
	else
		car->step = 1;
}

void	process_car(t_vm *core, t_car *car)
{
	int	i;

	core->car_cnt++;
	if (car->pc >= MEM_SIZE || car->pc < 0)
		vm_log(1, "Index ERROR carriage[%zu] = [%zd] current \"%s\"\n", car->id, car->pc,car->op_index >= 0 ? g_oplist[car->op_index].opname : "None");
	i = core->byte_owner[car->pc] - 1;
	if (i < core->n_players)
		core->champ[i]->car_cnt++;
	if (car->cooldown == 0 && car->op_index == -1)
		check_operation(core, car);
	if (car->cooldown != 0)
		car->cooldown--;
	if (car->cooldown == 0)
	{
		if (car->op_index != -1)
		{
			vm_log(F_LOG, "P%5zu | %s ", car->id + 1, g_oplist[car->op_index].opname);
			g_oplist[car->op_index].op(core, car);
			vm_log(F_LOG, "\n");
			car->op_index = -1;
		}
		car->pc = (car->pc + car->step) % MEM_SIZE;
		car->pc = car->pc < 0 ? MEM_SIZE + car->pc : car->pc;
	}
}

/*
** Needs optimization
*/

void	check_live_calls(t_vm *core)
{
	t_car *tmp;
	ssize_t limit;

	limit = core->cycles_to_die >= 0 ? core->cycle - core->cycles_to_die : core->cycle + core->cycles_to_die;
	limit = limit < 0 ? 0 : limit;
	limit = limit > core->cycle ? core->cycles_to_die : limit;
	tmp = core->car_list;
	vm_log(F_LOG, "[%zu]: Checking Lives:\n", core->cycle);
	while (tmp)
	{
		if (tmp->last_live < limit)
		{
			vm_log(F_LOG, "\n[%zu]: Carriage[%zu] failed to report live!\n", core->cycle, tmp->id);
			log_carriage(tmp, F_LOG);
			core->car_list = delete_carriage(core->car_list, tmp->id);
			tmp = core->car_list;
			core->car_cnt--;
		}
		else
			tmp = tmp->next;
	}
	vm_log(F_LOG, "Total carriages alive [%zu]\n", core->car_cnt);
}

void	print_reg(t_car *car)
{
	int cnt;

	cnt = 0;
	printf("REG %zu\n", car->id);
	printf("\tcarry: %d\n", car->carry);
	while (cnt < 16)
	{
		printf("\tn %d:\t%d\n", cnt + 1, car->reg[cnt]);
		cnt += 1;
	}
}

void	reset_car_cnt(t_vm *core)
{
	int cnt;

	cnt = 0;
	core->car_cnt = 0;
	while (cnt < core->n_players)
	{
		core->champ[cnt]->car_cnt = 0;
		cnt++;
	}
}

void	engine(t_vm *core)
{
	t_car	*current;

	core->checks = 0;
	core->cycle = 1;
	while (core->car_list && core->cycles_to_die >= 0)
	{
		if (core->cycle >= core->flags->dump_cycle)
		{
			print_arena(core->arena, core->flags->dump_size);
			log_arena(core->arena, core->flags->dump_size, F_LOG);
			log_vm_status(core, F_LOG);
			return ;
		}
		current = core->car_list;
		reset_car_cnt(core);
		while (current)
		{
			process_car(core, current);
			current = current->next;
		}
		if (core->check_cd <= 0)
		{
			check_live_calls(core);
			if (core->live_cnt >= 21 || core->checks == MAX_CHECKS)
			{
				core->cycles_to_die -= CYCLE_DELTA;
				core->checks = 0;
			}
			core->live_cnt = 0;
			core->check_cd = core->cycles_to_die;
			core->checks++;
		}
		
		core->check_cd--;
		core->cycle++;
	}
	core->cycle--;
	log_vm_status(core, F_LOG);
	if (core->last_to_live)
		ft_printf("[%zu] Player (%d) %s won\n", core->cycle, core->last_to_live->id, core->last_to_live->header->prog_name);
	else
		ft_printf("[%zu] Everyone is dead, total clusterfuck\n", core->cycle);
}

void	vfx_engine(t_vm *core)
{
	t_car	*current;
	size_t	loop;

	loop = 0;
	core->checks = 0;
	init_vfx_arena(core);
	draw_cycle(core);
	while (core->car_list && core->cycles_to_die >= 0)
	{
		if ((core->vfx->key = getch()) != ERR)
			vfx_key(core);
		if (VFX_PLAY && loop % core->vfx->freq == 0)
		{
			core->check_cd--;
			core->cycle++;
			loop = 0;
			current = core->car_list;
			reset_car_cnt(core);
			while (current)
			{
				process_car(core, current);
				current = current->next;
			}
			if (core->check_cd <= 0)
			{
				check_live_calls(core);
				if (core->live_cnt >= 21 || core->checks == MAX_CHECKS)
				{
					core->cycles_to_die -= CYCLE_DELTA;
					core->checks = 0;
				}
				core->live_cnt = 0;
				core->check_cd = core->cycles_to_die;
				core->checks++;
			}
			draw_cycle(core);
			if (core->cycle == core->flags->dump_cycle)
			{
				VFX_PLAY = 0;
				draw_cycle(core);
				log_vm_status(core, F_LOG);
			}
		}
		loop++;
	}
	wattron(stdscr, A_STANDOUT);
	wattron(stdscr, COLOR_PAIR(3));
	if (core->last_to_live)
		mvwprintw(VFX_INFO, core->vfx->info->height - 2, 2, "Player (%d) %s won\n", core->last_to_live->id, core->last_to_live->header->prog_name);
	else
		mvwprintw(VFX_INFO, core->vfx->info->height - 2, 2, "Everyone is dead, total clusterfuck\n");
	while (getch() != 27);
	endwin();
	log_vm_status(core, F_LOG);
}
