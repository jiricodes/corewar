/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op15_lfork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 15:02:59 by jnovotny          #+#    #+#             */
/*   Updated: 2020/08/06 19:36:11 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "oplist_cw.h"

inline void	log_lfork(t_vm *core, size_t car_id, int arg1, int arg2)
{
	char *tmp;

	if (!core->flags->vfx)
		ft_printf("[%zu]\tP %4zu | %s %d (%d)\n", core->cycle,\
			car_id, "lfork", arg1, arg2);
	else
	{
		tmp = ft_strnew(LOG_BUF);
		ft_sprintf(tmp, " [%zu]\tP %4zu | %s %d (%d)\n", core->cycle,\
			car_id, "lfork", arg1, arg2);
		vfx_write_log(core, tmp);
		free(tmp);
	}
}

void		op_lfork(t_vm *core, t_car *car)
{
	ssize_t	index;
	int		val;

	index = car->pc + OP_SIZE;
	if (read_args(core, car->args, index % MEM_SIZE))
	{
		val = ((car->pc + car->args->arg[0]) % MEM_SIZE);
		if (core->flags->log & LOG_OPS)
			log_lfork(core, car->id, car->args->arg[0], \
				car->pc + car->args->arg[0]);
		if (val < 0)
			val += MEM_SIZE;
		copy_carriage(core, car, val);
	}
	get_step(car, car->args);
}
