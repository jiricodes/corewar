/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op11_sti.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 15:02:59 by jnovotny          #+#    #+#             */
/*   Updated: 2020/07/25 15:10:53 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "oplist_cw.h"

static void	do_sti(t_args *args, t_car *car, t_vm *core)
{
	int	val[3];

	val[0] = car->reg[args->arg[0] - 1];
	if (args->arg_types[1] == T_IND)
		val[1] = read_arena(core->arena, car->pc, args->arg[1] % IDX_MOD, REG_SIZE);
	else if (args->arg_types[1] == T_DIR)
		val[1] = args->arg[1];
	else if (args->arg_types[1] == T_REG)
		val[1] = car->reg[args->arg[1] - 1];
	if (args->arg_types[2] == T_REG)
		val[2] = car->reg[args->arg[2] - 1];
	else if (args->arg_types[2] == T_DIR)
		val[2] = args->arg[2];
	write_bytes(car->pc + (val[1] + val[2]) % IDX_MOD, val[0], car, core);
}

void		op_sti(t_vm *core, t_car *car)
{
	ssize_t	index;

	if (F_LOG)
		vm_log(F_LOG, "[%zu]: Carriage[%zu] - operation \"%s\"\n", core->cycle,\
			car->id, g_oplist[car->op_index].opname);
	fill_args("sti", car->args);
	index = car->pc + OP_SIZE;
	if (read_arg_type(core->arena, car->args, index % MEM_SIZE))
	{
		index += ARG_SIZE;
		if (read_args(core->arena, car->args, index % MEM_SIZE))
			do_sti(car->args, car, core);
	}
	get_step(car, car->args);
}
