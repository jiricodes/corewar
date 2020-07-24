/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 17:08:32 by jnovotny          #+#    #+#             */
/*   Updated: 2020/07/24 20:29:15 by jnovotny         ###   ########.fr       */
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
		car->cooldown = g_oplist[car->op_index].exec_cycles;
	else
		car->step = 1;
}

void	process_car(t_vm *core, t_car *car)
{
	if (car->cooldown == 0 && car->op_index == -1)
		check_operation(core, car);
	if (car->cooldown != 0)
		car->cooldown--;
	else 
	{
		if (car->op_index != -1)
		{
			if (F_LOG)
				vm_log(F_LOG, "[%zu]: Carriage[%zu] should execute \"%s\"\n", core->cycle, car->id, g_oplist[car->op_index].opname);
			g_oplist[car->op_index].op(core, car);
			car->op_index = -1;
			// change car->step
		}
		car->pc = (car->pc + car->step) % MEM_SIZE;
	}
}

/*
** Needs optimization
*/

void	check_live_calls(t_vm *core)
{
	t_car *tmp;
	size_t limit;

	limit = core->cycle - core->cycles_to_die;
	tmp = core->car_list;
	while (tmp)
	{
		if (tmp->last_live < limit)
		{
			if (F_LOG)
				vm_log(F_LOG, "[%zu]: Carriage[%zu] failed to report live\n", core->cycle, tmp->id);
			core->car_list = delete_carriage(core->car_list, tmp->id);
			tmp = core->car_list;
		}
		else
			tmp = tmp->next;
	}
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

void	engine(t_vm *core)
{
	t_car	*current;
	int		checks;
	size_t	loop;

	loop = 0;
	checks = 0;
	if (VFX)
	{
		init_vfx_arena(core);
		mvprintw(0,0, "Cycle: %zu", core->cycle);
		draw_arena(core);
	}
	while (core->car_list && core->cycles_to_die > 0)
	{
		// printf("Cycle %zu\n", core->cycle);
		if (VFX && (core->vfx->key = getch()) != ERR)
			vfx_key(core->vfx);
		if (VFX)
			mvprintw(0,35, "Frequency %zu", core->vfx->freq);
		if (!VFX || (core->vfx->play && loop % core->vfx->freq == 0))
		{
			loop = 0;
			current = core->car_list;
			while (current)
			{
				// log_carriage(current);
				process_car(core, current);
				// if (F_LOG == 2)
				// 	print_reg(current);
				current = current->next;
				// show_arena(core);
			}
			core->cycle++;
			core->check_cd--;
			if (core->check_cd <= 0)
			{
				check_live_calls(core);
				checks++;
				if (core->live_cnt >= 21 || checks == MAX_CHECKS)
				{
					if (core->cycles_to_die >= CYCLE_DELTA)
						core->cycles_to_die -= CYCLE_DELTA;
					else
						core->cycles_to_die = 0;
					checks = 0;
					core->live_cnt = 0;
				}
				core->check_cd = core->cycles_to_die;
			}
			if (VFX)
			{
				mvprintw(0,0, "Cycle: %zu", core->cycle);
				draw_arena(core);
				// nanosleep(&(core->vfx->time), NULL);
			}
			if (core->cycle == core->flags->dump_cycle)
			{
				print_arena(core->arena, core->flags->dump_size);
				return ;
			}
		}
		// ft_printf("Cycle to die: %zu\n", core->cycles_to_die);
		loop++;
	}
	if (VFX)
	{
		wattron(stdscr, A_STANDOUT);
		wattron(stdscr, COLOR_PAIR(3));
		if (core->last_to_live)
			mvprintw(0, 55, "Player (%d) %s won\n", core->last_to_live->id, core->last_to_live->header->prog_name);
		else
			mvprintw(0, 55, "Everyone is dead, total clusterfuck\n");
		while (getch() != 27);
		endwin();
	}
	if (core->last_to_live)
		ft_printf("Player (%d) %s won\n", core->last_to_live->id, core->last_to_live->header->prog_name);
	else
		ft_printf("Everyone is dead, total clusterfuck\n");
}