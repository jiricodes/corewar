/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op14.lldi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 15:02:59 by jnovotny          #+#    #+#             */
/*   Updated: 2020/07/29 18:19:24 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "oplist_cw.h"

static void	do_lldi(t_vm *core, t_args *args, t_car *car)
{
	int	val[3];

	vm_log(core->flags->log, OP_STR, core->cycle, car->id + 1, "lldi");
	if (args->arg_types[0] == T_IND)
		val[0] = read_arena(core->arena, car->pc,\
			args->arg[0] % IDX_MOD, REG_SIZE);
	else if (args->arg_types[0] == T_DIR)
		val[0] = args->arg[0];
	else if (args->arg_types[0] == T_REG)
		val[0] = car->reg[args->arg[0] - 1];
	if (args->arg_types[1] == T_REG)
		val[1] = car->reg[args->arg[1] - 1];
	else if (args->arg_types[1] == T_DIR)
		val[1] = args->arg[1];
	val[2] = args->arg[2];
	car->reg[val[2] - 1] = read_arena(core->arena, car->pc,\
		val[0] + val[1], REG_SIZE);
	vm_log(core->flags->log, "%d %d r%d\n", val[0], val[1], val[2]);
}

void		op_lldi(t_vm *core, t_car *car)
{
	ssize_t	start;

	start = car->pc + OP_SIZE;
	if (read_arg_type(core->arena, car->args, start % MEM_SIZE))
	{
		start += ARG_SIZE;
		if (read_args(core, car->args, start % MEM_SIZE))
			do_lldi(core, car->args, car);
	}
	get_step(car, car->args);
}
