/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op16_aff.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 15:02:59 by jnovotny          #+#    #+#             */
/*   Updated: 2020/08/04 18:12:33 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "oplist_cw.h"

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
				{
					ft_printf(OP_STR, core->cycle, car->id, "aff");
					ft_printf("%d\n", val);
				}
			}
		}
	}
	get_step(car, car->args);
}
