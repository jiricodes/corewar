/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op10_ldi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolopov <asolopov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 15:02:59 by jnovotny          #+#    #+#             */
/*   Updated: 2020/07/27 15:33:45 by asolopov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "oplist_cw.h"

static void	do_ldi(uint8_t *arena, t_args *args, t_car *car)
{
	int		val[3];

	if (args->arg_types[0] == T_IND)
		val[0] = read_arena(arena, car->pc, args->arg[0] % IDX_MOD, REG_SIZE);
	else if (args->arg_types[0] == T_DIR)
		val[0] = args->arg[0];
	else if (args->arg_types[0] == T_REG)
		val[0] = car->reg[args->arg[0] - 1];
	if (args->arg_types[1] == T_REG)
		val[1] = car->reg[args->arg[1] - 1];
	else if (args->arg_types[1] == T_DIR)
		val[1] = args->arg[1];
	val[2] = args->arg[2];
	car->reg[val[2] - 1] = read_arena(arena, car->pc, \
							(val[0] + val[1]) % IDX_MOD, REG_SIZE);
}

void		op_ldi(t_vm *core, t_car *car)
{
	ssize_t	start;

	vm_log(F_LOG, "P\t%zu | %s", car->id, g_oplist[car->op_index].opname);
	fill_args("ldi", car->args);
	start = car->pc + OP_SIZE;
	if (read_arg_type(core->arena, car->args, start % MEM_SIZE))
	{
		start += ARG_SIZE;
		if (read_args(core, car->args, start % MEM_SIZE))
			do_ldi(core->arena, car->args, car);
	}
	vm_log(F_LOG, "\n");
	get_step(car, car->args);
}
