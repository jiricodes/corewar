/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op04_add.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 15:02:59 by jnovotny          #+#    #+#             */
/*   Updated: 2020/08/06 18:42:27 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "oplist_cw.h"

inline void	log_add(t_vm *core, size_t car_id, int arg[3])
{
	char *tmp;

	if (!core->flags->vfx)
		ft_printf("[%zu]\tP %4zu | %s r%d r%d r%d\n", core->cycle, car_id,\
			"add", arg[0], arg[1], arg[2]);
	else
	{
		tmp = ft_strnew(LOG_BUF);
		ft_sprintf(tmp, " [%zu]\tP %4zu | %s r%d r%d r%d\n", core->cycle,\
			car_id, "add", arg[0], arg[1], arg[2]);
		vfx_write_log(core, tmp);
		free(tmp);
	}
}

static void	do_add(t_vm *core, t_args *args, t_car *car)
{
	int	val[3];

	val[0] = car->reg[args->arg[0] - 1];
	val[1] = car->reg[args->arg[1] - 1];
	val[2] = args->arg[2] - 1;
	car->reg[val[2]] = val[0] + val[1];
	car->carry = car->reg[val[2]] ? 0 : 1;
	if (core->flags->log & LOG_OPS)
		log_add(core, car->id, args->arg);
}

void		op_add(t_vm *core, t_car *car)
{
	ssize_t	index;

	index = car->pc + OP_SIZE;
	if (read_arg_type(core->arena, car->args, index % MEM_SIZE))
	{
		index += ARG_SIZE;
		if (read_args(core, car->args, index % MEM_SIZE))
			do_add(core, car->args, car);
	}
	get_step(car, car->args);
}
