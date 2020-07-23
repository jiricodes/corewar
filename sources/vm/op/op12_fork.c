/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op12_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolopov <asolopov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 15:02:59 by jnovotny          #+#    #+#             */
/*   Updated: 2020/07/23 14:07:01 by asolopov         ###   ########.fr       */
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
	uint8_t	*code;
	int		val;

	if (LOG)
		vm_log("Carriage[%zu] - operation \"%s\"\n", car->id, g_oplist[car->op_index].opname);
	fill_args("fork", car->args);
	code = core->arena + car->pc + OP_BYTE;
	val = decode(code, car->args->t_dir_size) % IDX_MOD;
	copy_carriage(core, car, val);
	get_step(car, car->args);
	printf("fork\n");
}
