/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op02_ld.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 15:02:59 by jnovotny          #+#    #+#             */
/*   Updated: 2020/08/07 07:25:44 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "oplist_cw.h"

inline void	log_ld(t_vm *core, t_car *car, int val[2])
{
	char *tmp;

	if (!core->flags->vfx)
		ft_printf("[%zu]\tP %4zu | %s %d r%d\n", core->cycle, car->id,\
			"ld", val[0], val[1]);
	else
	{
		tmp = ft_strnew(LOG_BUF);
		ft_sprintf(tmp, " [%zu]\tP %4zu | %s %d r%d\n",\
			core->cycle, car->id, "ld", val[0], val[1]);
		vfx_write_log(core, tmp, car->pc);
		free(tmp);
	}
}

static void	do_ld(t_vm *core, t_args *args, t_car *car)
{
	int	val[2];

	if (args->arg_types[0] == T_DIR)
		val[0] = args->arg[0];
	else if (args->arg_types[0] == T_IND)
		val[0] = read_arena(core->arena, car->pc,\
			args->arg[0] % IDX_MOD, REG_SIZE);
	val[1] = args->arg[1];
	car->reg[val[1] - 1] = val[0];
	car->carry = (car->reg[val[1] - 1]) ? 0 : 1;
	if (core->flags->log & LOG_OPS)
		log_ld(core, car, val);
}

void		op_ld(t_vm *core, t_car *car)
{
	ssize_t	index;

	index = car->pc + OP_SIZE;
	if (read_arg_type(core->arena, car->args, index % MEM_SIZE))
	{
		index += ARG_SIZE;
		if (read_args(core, car->args, index % MEM_SIZE))
			do_ld(core, car->args, car);
	}
	get_step(car, car->args);
}
