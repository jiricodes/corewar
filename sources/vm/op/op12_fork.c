/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op12_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 15:02:59 by jnovotny          #+#    #+#             */
/*   Updated: 2020/08/06 19:26:10 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "oplist_cw.h"

inline void	log_fork(t_vm *core, size_t car_id, int arg, int val)
{
	char *tmp;

	if (!core->flags->vfx)
		ft_printf("[%zu]\tP %4zu | %s %d (%d)\n", core->cycle,\
			car_id, "fork", arg, val);
	else
	{
		tmp = ft_strnew(LOG_BUF);
		ft_sprintf(tmp, " [%zu]\tP %4zu | %s %d (%d)\n", core->cycle,\
			car_id, "fork", arg, val);
		vfx_write_log(core, tmp);
		free(tmp);
	}
}

void	op_fork(t_vm *core, t_car *car)
{
	ssize_t	index;
	int		val;

	index = car->pc + OP_SIZE;
	if (read_args(core, car->args, index % MEM_SIZE))
	{
		val = (car->pc + car->args->arg[0] % IDX_MOD) % MEM_SIZE;
		if (core->flags->log & LOG_OPS)
			log_fork(core, car->id, car->args->arg[0], val);
		if (val < 0)
			val += MEM_SIZE;
		copy_carriage(core, car, val);
	}
	get_step(car, car->args);
}
