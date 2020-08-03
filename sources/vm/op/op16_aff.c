/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op16_aff.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 15:02:59 by jnovotny          #+#    #+#             */
/*   Updated: 2020/08/03 14:05:17 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "oplist_cw.h"

void	op_aff(t_vm *core, t_car *car)
{
	ssize_t	index;
	char	val;

	index = car->pc + OP_SIZE;
	if (read_args(core, car->args, index % MEM_SIZE))
	{
		val = (char)(car->reg[car->args->arg[0] - 1] % 256);
		if (core->flags->log & LOG_OPS)
		{
			vm_log(core->flags->log, OP_STR, core->cycle, car->id + 1, "aff");
			vm_log(core->flags->log, "%d\n", val);
		}
		if (core->flags->aff)
		{
			ft_putchar(val);
			ft_putchar('\n');
		}
	}
	get_step(car, car->args);
}
