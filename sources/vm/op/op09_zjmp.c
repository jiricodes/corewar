/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op09_zjmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 15:02:59 by jnovotny          #+#    #+#             */
/*   Updated: 2020/07/27 13:02:55 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "oplist_cw.h"

void	op_zjmp(t_vm *core, t_car *car)
{
	ssize_t	index;
	int		val;

	vm_log(F_LOG, "[%zu]: Carriage[%zu] - operation \"%s\"", core->cycle,\
		car->id, g_oplist[car->op_index].opname);
	fill_args("zjmp", car->args);
	index = car->pc + OP_SIZE;
	if (read_args(core->arena, car->args, index % MEM_SIZE))
	{
		val = car->args->arg[0];
		vm_log(F_LOG, " arg = %d", val);
		if (car->carry)
		{
			car->step = val % IDX_MOD;
			vm_log(F_LOG, " | OK -> step = %zd\n", car->step);
			return ;
		}
	}
	vm_log(F_LOG, "\n");
	get_step(car, car->args);
}
