/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op13_lld.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 15:02:59 by jnovotny          #+#    #+#             */
/*   Updated: 2020/07/24 20:05:54 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "oplist_cw.h"

static void	do_lld(uint8_t *arena, t_args *args, t_car *car)
{
	int	val[2];

	if (args->arg_types[0] == T_DIR)
		val[0] = args->arg[0];
	else if (args->arg_types[0] == T_IND)
		val[0] = read_arena(arena, car->pc, args->arg[0], REG_SIZE);
	val[1] = args->arg[1] - 1;
	car->reg[val[1]] = val[0];
	car->carry = (car->reg[val[1]]) ? 0 : 1;
}

void		op_lld(t_vm *core, t_car *car)
{
	ssize_t	start;

	if (F_LOG)
		vm_log(F_LOG, "Carriage[%zu] - operation \"%s\"\n", car->id,\
			g_oplist[car->op_index].opname);
	fill_args("lld", car->args);
	start = car->pc + OP_SIZE;
	if (read_arg_type(core->arena, car->args, start % MEM_SIZE))
	{
		start += ARG_SIZE;
		if (read_args(core->arena, car->args, start % MEM_SIZE))
			do_lld(core->arena, car->args, car);
	}
	get_step(car, car->args);
}
