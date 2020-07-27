/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op16_aff.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolopov <asolopov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 15:02:59 by jnovotny          #+#    #+#             */
/*   Updated: 2020/07/27 15:42:08 by asolopov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "oplist_cw.h"

void	op_aff(t_vm *core, t_car *car)
{
	ssize_t	index;
	int		val;

	fill_args("aff", car->args);
	index = car->pc + OP_SIZE;
	if (read_args(core, car->args, index % MEM_SIZE))
	{
		val = (char)(car->reg[car->args->arg[0] - 1]);
		if (core->flags->aff)
			ft_putchar(val);
	}
	get_step(car, car->args);
}
