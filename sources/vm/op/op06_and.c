/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op06_and.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 15:02:59 by jnovotny          #+#    #+#             */
/*   Updated: 2020/08/04 18:11:54 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "oplist_cw.h"

static void	do_and(t_vm *core, t_args *args, t_car *car)
{
	int		val[3];
	int		cnt;

	cnt = 0;
	while (cnt < 2)
	{
		if (args->arg_types[cnt] == T_REG)
			val[cnt] = car->reg[args->arg[cnt] - 1];
		else if (args->arg_types[cnt] == T_IND)
			val[cnt] = read_arena(core->arena, car->pc,\
				args->arg[cnt] % IDX_MOD, REG_SIZE);
		else if (args->arg_types[cnt] == T_DIR)
			val[cnt] = args->arg[cnt];
		cnt += 1;
	}
	val[2] = args->arg[2];
	car->reg[val[2] - 1] = val[0] & val[1];
	car->carry = car->reg[val[2] - 1] ? 0 : 1;
	if (core->flags->log & LOG_OPS)
	{
		ft_printf(OP_STR, core->cycle, car->id, "and");
		ft_printf("%d %d r%d\n", val[0], val[1], val[2]);
	}
}

void		op_and(t_vm *core, t_car *car)
{
	ssize_t	start;

	start = car->pc + OP_SIZE;
	if (read_arg_type(core->arena, car->args, start % MEM_SIZE))
	{
		start += ARG_SIZE;
		if (read_args(core, car->args, start % MEM_SIZE))
			do_and(core, car->args, car);
	}
	get_step(car, car->args);
}
