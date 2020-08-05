/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op12_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 15:02:59 by jnovotny          #+#    #+#             */
/*   Updated: 2020/08/04 18:12:20 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "oplist_cw.h"

void	op_fork(t_vm *core, t_car *car)
{
	ssize_t	index;
	int		val;

	index = car->pc + OP_SIZE;
	if (read_args(core, car->args, index % MEM_SIZE))
	{
		val = (car->pc + car->args->arg[0] % IDX_MOD) % MEM_SIZE;
		if (core->flags->log & LOG_OPS)
		{
			ft_printf(OP_STR, core->cycle, car->id, "fork");
			ft_printf("%d (%d)\n", car->args->arg[0], val);
		}
		if (val < 0)
			val += MEM_SIZE;
		copy_carriage(core, car, val);
	}
	get_step(car, car->args);
}
