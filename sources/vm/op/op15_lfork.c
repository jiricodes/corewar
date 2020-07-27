/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op15_lfork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolopov <asolopov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 15:02:59 by jnovotny          #+#    #+#             */
/*   Updated: 2020/07/27 15:42:09 by asolopov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "oplist_cw.h"

void		op_lfork(t_vm *core, t_car *car)
{
	ssize_t	index;
	int		val;

	fill_args("lfork", car->args);
	index = car->pc + OP_SIZE;
	if (read_args(core, car->args, index % MEM_SIZE))
	{
		val = (car->pc + car->args->arg[0]) % MEM_SIZE;
		vm_log(F_LOG, " (%d)", val);
		copy_carriage(core, car, val);
	}
	get_step(car, car->args);
}
