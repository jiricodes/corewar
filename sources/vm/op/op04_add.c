/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op04_add.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolopov <asolopov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 15:02:59 by jnovotny          #+#    #+#             */
/*   Updated: 2020/07/28 17:47:46 by asolopov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "oplist_cw.h"

static void	do_add(t_vm *core, t_args *args, t_car *car)
{
	int	val[3];

	vm_log(F_LOG, OP_STR, core->cycle, car->id + 1, "add");
	val[0] = car->reg[args->arg[0] - 1];
	val[1] = car->reg[args->arg[1] - 1];
	val[2] = args->arg[2] - 1;
	car->reg[val[2]] = val[0] + val[1];
	car->carry = car->reg[val[2]] ? 0 : 1;
	vm_log(F_LOG, "r%d r%d r%d\n", args->arg[0], args->arg[1], args->arg[2]);
}

void		op_add(t_vm *core, t_car *car)
{
	ssize_t	index;

	index = car->pc + OP_SIZE;
	if (read_arg_type(core->arena, car->args, index % MEM_SIZE))
	{
		index += ARG_SIZE;
		if (read_args(core, car->args, index % MEM_SIZE))
			do_add(core, car->args, car);
	}
	get_step(car, car->args);
}
