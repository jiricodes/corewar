/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 17:08:32 by jnovotny          #+#    #+#             */
/*   Updated: 2020/07/16 17:38:44 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
void	process_car(t_vm *core, t_car *car)
{
	// if (car->cooldown == 0)
	// 	check_opcode()
	// if (car->cooldown != 0)
	// 	car->cooldown--;
	// else
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