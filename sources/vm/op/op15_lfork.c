/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op15_lfork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 15:02:59 by jnovotny          #+#    #+#             */
/*   Updated: 2020/08/07 07:25:03 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "oplist_cw.h"

inline void	log_lfork(t_vm *core, t_car *car, int arg1, int arg2)
{
	char *tmp;

	if (!core->flags->vfx)
		ft_printf("[%zu]\tP %4zu | %s %d (%d)\n", core->cycle,\
			car->id, "lfork", arg1, arg2);
	else
	{
		tmp = ft_strnew(LOG_BUF);
		ft_sprintf(tmp, " [%zu]\tP %4zu | %s %d (%d)\n", core->cycle,\
			car->id, "lfork", arg1, arg2);
		vfx_write_log(core, tmp, car->pc);
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
			log_lfork(core, car, car->args->arg[0], \
				car->pc + car->args->arg[0]);
		if (val < 0)
			val += MEM_SIZE;
		copy_carriage(core, car, val);
	}
	get_step(car, car->args);
}
