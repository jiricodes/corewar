/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op03_st.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 15:02:59 by jnovotny          #+#    #+#             */
/*   Updated: 2020/08/07 07:22:20 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "oplist_cw.h"

inline void	log_st(t_vm *core, t_car *car, int arg, int val)
{
	char *tmp;

	if (!core->flags->vfx)
		ft_printf("[%zu]\tP %4zu | %s r%d %d\n", core->cycle,\
			car->id, "st", arg, val);
	else
	{
		tmp = ft_strnew(LOG_BUF);
		ft_sprintf(tmp, " [%zu]\tP %4zu | %s r%d %d\n", core->cycle,\
			car->id, "st", arg, val);
		vfx_write_log(core, tmp, car->pc);
		free(tmp);
	}
}

static void	do_st(t_vm *core, t_args *args, t_car *car)
{
	int32_t	val[2];

	val[0] = car->reg[args->arg[0] - 1];
	if (args->arg_types[1] == T_IND)
	{
		val[1] = args->arg[1];
		write_bytes(car->pc + val[1] % IDX_MOD, val[0], car, core);
	}
	else if (args->arg_types[1] == T_REG)
	{
		val[1] = args->arg[1];
		car->reg[val[1] - 1] = val[0];
	}
	if (core->flags->log & LOG_OPS)
		log_st(core, car, args->arg[0], val[1]);
}

void		op_st(t_vm *core, t_car *car)
{
	ssize_t	index;

	index = car->pc + OP_SIZE;
	if (read_arg_type(core->arena, car->args, index % MEM_SIZE))
	{
		index += ARG_SIZE;
		if (read_args(core, car->args, index % MEM_SIZE))
			do_st(core, car->args, car);
	}
	get_step(car, car->args);
}
