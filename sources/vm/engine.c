/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 17:08:32 by jnovotny          #+#    #+#             */
/*   Updated: 2020/07/16 17:59:25 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
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
	if (car->cooldown == 0)
		check_operation(core, car);
	if (car->cooldown != 0)
		car->cooldown--;
	else 
	{
		if (car->op_index != -1)
		{
			// to be created
		}
		car->pc += car->step;
	}
}

void	engine(t_vm *core)
{
	t_car	*current;

	while (core->car_list)
	{
		current = core->car_list;
		while (current)
		{
			process_car(core, current);
			show_arena(core);
			core->cycle++;
			core->check_cd--;
			if (core->check_cd == 0)
			{
				// check if they called live
				if (core->live_cnt >= 21)
					core->cycles_to_die -= CYCLE_DELTA;
				// core->check_cd = core->cycles_to_die;
			}
		}
	}
}