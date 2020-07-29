/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op12_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 15:02:59 by jnovotny          #+#    #+#             */
/*   Updated: 2020/07/29 18:17:27 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "oplist_cw.h"

void	op_fork(t_vm *core, t_car *car)
{
	ssize_t	index;
	int		val;

	index = car->pc + OP_SIZE;
	if (read_args(core, car->args, index % MEM_SIZE))
	{
		vm_log(core->flags->log, OP_STR, core->cycle, car->id + 1, "fork");
		val = (car->pc + car->args->arg[0] % IDX_MOD) % MEM_SIZE;
		vm_log(core->flags->log, "%d (%d)\n", car->args->arg[0], val);
		copy_carriage(core, car, val);
	}
	get_step(car, car->args);
}
