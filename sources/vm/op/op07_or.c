/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op07_or.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 15:02:59 by jnovotny          #+#    #+#             */
/*   Updated: 2020/08/07 07:23:01 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "oplist_cw.h"

inline void	log_or(t_vm *core, t_car *car, int val[3])
{
	char *tmp;

	if (!core->flags->vfx)
		ft_printf("[%zu]\tP %4zu | %s %d %d r%d\n", core->cycle,\
			car->id, "or", val[0], val[1], val[2]);
	else
	{
		tmp = ft_strnew(LOG_BUF);
		ft_sprintf(tmp, " [%zu]\tP %4zu | %s %d %d r%d\n", core->cycle,\
			car->id, "or", val[0], val[1], val[2]);
		vfx_write_log(core, tmp, car->pc);
		free(tmp);
	}
}

static void	do_or(t_vm *core, t_args *args, t_car *car)
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
	car->reg[val[2] - 1] = val[0] | val[1];
	car->carry = car->reg[val[2] - 1] ? 0 : 1;
	if (core->flags->log & LOG_OPS)
		log_or(core, car, val);
}

void		op_or(t_vm *core, t_car *car)
{
	ssize_t	index;

	index = car->pc + OP_SIZE;
	if (read_arg_type(core->arena, car->args, index % MEM_SIZE))
	{
		index += ARG_SIZE;
		if (read_args(core, car->args, index % MEM_SIZE))
			do_or(core, car->args, car);
	}
	get_step(car, car->args);
}
