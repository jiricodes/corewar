/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op13_lld.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 15:02:59 by jnovotny          #+#    #+#             */
/*   Updated: 2020/08/04 18:12:23 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "oplist_cw.h"

static void	do_lld(t_vm *core, t_args *args, t_car *car)
{
	int	val[2];

	if (args->arg_types[0] == T_DIR)
		val[0] = args->arg[0];
	else if (args->arg_types[0] == T_IND)
		val[0] = read_arena(core->arena, car->pc, args->arg[0], REG_SIZE);
	val[1] = args->arg[1];
	car->reg[val[1] - 1] = val[0];
	car->carry = (car->reg[val[1] - 1]) ? 0 : 1;
	if (core->flags->log & LOG_OPS)
	{
		ft_printf(OP_STR, core->cycle, car->id, "lld");
		ft_printf("%d r%d\n", val[0], val[1]);
	}
}

void		op_lld(t_vm *core, t_car *car)
{
	ssize_t	index;

	index = car->pc + OP_SIZE;
	if (read_arg_type(core->arena, car->args, index % MEM_SIZE))
	{
		index += ARG_SIZE;
		if (read_args(core, car->args, index % MEM_SIZE))
			do_lld(core, car->args, car);
	}
	get_step(car, car->args);
}
