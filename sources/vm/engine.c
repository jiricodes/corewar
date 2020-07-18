/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 17:08:32 by jnovotny          #+#    #+#             */
/*   Updated: 2020/07/18 16:09:04 by jnovotny         ###   ########.fr       */
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
			return (g_oplist[cnt].opcode);
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
			if (LOG)
				vm_log("[%zu]: Carriage[%zu] should execute \"%s\"\n", core->cycle, car->id, g_oplist[car->op_index].opname);
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
			if (LOG)
				vm_log("[%zu]: Carriage[%zu] failed to report live\n", core->cycle, tmp->id);
			core->car_list = delete_carriage(core->car_list, tmp->id);
			tmp = core->car_list;
		}
		else
			tmp = tmp->next;
	}
}

void	engine(t_vm *core)
{
	t_car	*current;
	int		checks;

	checks = 0;
	if (VFX)
		init_vfx_arena(core);
	while (core->car_list && core->cycles_to_die > 0)
	{
		// printf("Cycle %zu\n", core->cycle);
		current = core->car_list;
		while (current)
		{
			// log_carriage(current);
			process_car(core, current);
			current = current->next;
			// show_arena(core);
		}
		core->cycle++;
		core->check_cd--;
		if (core->check_cd == 0)
		{
			check_live_calls(core);
			if (core->live_cnt >= 21 || checks == MAX_CHECKS)
			{
				core->cycles_to_die -= CYCLE_DELTA;
				checks = 0;
			}
			core->check_cd = core->cycles_to_die;
		}
		if (VFX)
		{
			draw_arena(core);
			nanosleep(&(core->vfx->time), NULL);
		}
	}
	if (VFX)
	{
		getch();
		endwin();
	}
	if (core->last_to_live)
		ft_printf("Player (%d) %s won\n", core->last_to_live->id, core->last_to_live->header->prog_name);
	else
		ft_printf("Everyone is dead, total clusterfuck\n");
}