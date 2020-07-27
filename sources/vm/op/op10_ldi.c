/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op10_ldi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolopov <asolopov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 15:02:59 by jnovotny          #+#    #+#             */
/*   Updated: 2020/07/27 16:34:55 by asolopov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "oplist_cw.h"

static void	do_ldi(t_vm *core, t_args *args, t_car *car)
{
	int		val[3];

	if (args->arg_types[0] == T_IND)
		val[0] = read_arena(core->arena, car->pc, args->arg[0] % IDX_MOD, REG_SIZE);
	else if (args->arg_types[0] == T_DIR)
		val[0] = args->arg[0];
	else if (args->arg_types[0] == T_REG)
		val[0] = car->reg[args->arg[0] - 1];
	if (args->arg_types[1] == T_REG)
		val[1] = car->reg[args->arg[1] - 1];
	else if (args->arg_types[1] == T_DIR)
		val[1] = args->arg[1];
	val[2] = args->arg[2];
	car->reg[val[2] - 1] = read_arena(core->arena, car->pc, \
							(val[0] + val[1]) % IDX_MOD, REG_SIZE);
	vm_log(F_LOG, "%d %d r%d\n", val[0], val[1], val[2]);
	vm_log(F_LOG, "-> load from %d + %d = %d", val[0], val[1], val[0] + val[1]);
}

void		op_ldi(t_vm *core, t_car *car)
{
	ssize_t	start;

	fill_args("ldi", car->args);
	start = car->pc + OP_SIZE;
	if (read_arg_type(core->arena, car->args, start % MEM_SIZE))
	{
		start += ARG_SIZE;
		if (read_args(core, car->args, start % MEM_SIZE))
		{
			vm_log(F_LOG, "P\t%zu | %s", car->id, g_oplist[car->op_index].opname);
			do_ldi(core, car->args, car);
		}
	}
	get_step(car, car->args);
}
