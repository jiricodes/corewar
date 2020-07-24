/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op12_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 15:02:59 by jnovotny          #+#    #+#             */
/*   Updated: 2020/07/24 19:47:12 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "oplist_cw.h"

static void	copy_carriage(t_vm *core, t_car *car, int addr)
{
	t_car *new;
	int cnt;

	cnt = 0;
	new = create_carriage(core->car_id, addr, 0);
	core->car_id += 1;
	while (cnt < 16)
	{
		new->reg[cnt] = car->reg[cnt];
		cnt += 1;
	}
	new->carry = car->carry;
	new->last_live = car->last_live;
	prepend_carriage(new, core->car_list);
}

void		op_fork(t_vm *core, t_car *car)
{
	ssize_t	index;
	int		val;

	if (F_LOG)
		vm_log(F_LOG, "Carriage[%zu] - operation \"%s\"\n", car->id, g_oplist[car->op_index].opname);
	fill_args("fork", car->args);
	index = car->pc + OP_SIZE;
	if (read_args(core->arena, car->args, index % MEM_SIZE))
	{
		val = car->pc + car->args->arg[0] % IDX_MOD;
		copy_carriage(core, car, val);
	}
	get_step(car, car->args);
}
