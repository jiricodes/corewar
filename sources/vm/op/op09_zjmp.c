/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op09_zjmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 15:02:59 by jnovotny          #+#    #+#             */
/*   Updated: 2020/08/06 19:23:09 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "oplist_cw.h"

inline void	log_zjmp(t_vm *core, size_t car_id, int val, char *stat)
{
	char	*tmp;

	if (!core->flags->vfx)
		ft_printf("[%zu]\tP %4zu | %s %d %s\n", core->cycle,\
			car_id, "zjmp", val, stat);
	else
	{
		tmp = ft_strnew(LOG_BUF);
		ft_sprintf(tmp, " [%zu]\tP %4zu | %s %d %s\n", core->cycle,\
			car_id, "zjmp", val, stat);
		vfx_write_log(core, tmp);
		free(tmp);
	}
}

void		op_zjmp(t_vm *core, t_car *car)
{
	int		val;
	ssize_t	index;

	val = 0;
	index = car->pc + OP_SIZE;
	if (read_args(core, car->args, index % MEM_SIZE))
	{
		val = car->args->arg[0];
		if (car->carry)
		{
			car->step = val % IDX_MOD;
			if (core->flags->log & LOG_OPS)
				log_zjmp(core, car->id, val, "OK");
			return ;
		}
	}
	if (core->flags->log & LOG_OPS)
		log_zjmp(core, car->id, val, "FAILED");
	get_step(car, car->args);
}
