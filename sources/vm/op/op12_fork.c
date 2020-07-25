/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op12_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 15:02:59 by jnovotny          #+#    #+#             */
/*   Updated: 2020/07/25 15:32:05 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "oplist_cw.h"

void	op_fork(t_vm *core, t_car *car)
{
	ssize_t	index;
	int		val;

	if (F_LOG)
		vm_log(F_LOG, "[%zu]: Carriage[%zu] - operation \"%s\"\n", core->cycle,\
			car->id, g_oplist[car->op_index].opname);
	fill_args("fork", car->args);
	index = car->pc + OP_SIZE;
	if (read_args(core->arena, car->args, index % MEM_SIZE))
	{
		val = (car->pc + car->args->arg[0] % IDX_MOD) % MEM_SIZE;
		copy_carriage(core, car, val);
	}
	get_step(car, car->args);
}
