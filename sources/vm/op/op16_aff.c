/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op16_aff.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 15:02:59 by jnovotny          #+#    #+#             */
/*   Updated: 2020/08/06 19:37:42 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "oplist_cw.h"

inline void	log_aff(t_vm *core, size_t car_id, int val)
{
	char *tmp;

	if (!core->flags->vfx)
		ft_printf("[%zu]\tP %4zu | %s %d\n", core->cycle, car_id, "aff", val);
	else
	{
		tmp = ft_strnew(LOG_BUF);
		ft_sprintf(tmp, " [%zu]\tP %4zu | %s %d\n",\
			core->cycle, car_id, "aff", val);
		vfx_write_log(core, tmp);
		free(tmp);
	}
}

void	op_aff(t_vm *core, t_car *car)
{
	ssize_t	index;
	char	val;

	index = car->pc + OP_SIZE;
	if (read_arg_type(core->arena, car->args, index % MEM_SIZE))
	{
		index += ARG_SIZE;
		if (read_args(core, car->args, index % MEM_SIZE))
		{
			val = (char)(car->reg[car->args->arg[0] - 1] % 256);
			if (core->flags->aff)
			{
				ft_putchar(val);
				ft_putchar('\n');
				if (core->flags->log & LOG_OPS)
					log_aff(core, car->id, val);
			}
		}
	}
	get_step(car, car->args);
}
