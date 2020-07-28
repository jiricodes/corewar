/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op09_zjmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolopov <asolopov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 15:02:59 by jnovotny          #+#    #+#             */
/*   Updated: 2020/07/28 18:00:54 by asolopov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "oplist_cw.h"

void	op_zjmp(t_vm *core, t_car *car)
{
	int		val;
	ssize_t	index;

	val = 0;
	index = car->pc + OP_SIZE;
	if (read_args(core, car->args, index % MEM_SIZE))
	{
		val = car->args->arg[0];
		if (car->carry)
		{
			vm_log(F_LOG, OP_STR, core->cycle, car->id + 1, "zjmp");
			car->step = val % IDX_MOD;
			vm_log(F_LOG, "%d OK\n", car->step);
			return ;
		}
	}
	vm_log(F_LOG, OP_STR, core->cycle, car->id + 1, "zjmp");
	vm_log(F_LOG, "%d FAILED\n", val % IDX_MOD);
	get_step(car, car->args);
}
