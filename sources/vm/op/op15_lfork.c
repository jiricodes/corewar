/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op15_lfork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolopov <asolopov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 15:02:59 by jnovotny          #+#    #+#             */
/*   Updated: 2020/07/23 14:06:53 by asolopov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "oplist_cw.h"

static void	copy_carriage(t_vm *core, t_car *car, int addr)
{
	t_car *new;
	int cnt;

	cnt = 0;
	new = create_carriage(car->id, addr, 0);
	while (cnt < 16)
	{
		new->reg[cnt] = car->reg[cnt];
		cnt += 1;
	}
	new->carry = car->carry;
	new->last_live = car->last_live;
	prepend_carriage(new, core->car_list);
	// append_carriage(new, core->car_list);
}

void		op_lfork(t_vm *core, t_car *car)
{
	uint8_t	*code;
	int		val;
	
	if (LOG)
		vm_log("Carriage[%zu] - operation \"%s\"\n", car->id, g_oplist[car->op_index].opname);
	fill_args("lfork", car->args);
	code = core->arena + car->pc + OP_BYTE;
	val = decode(code, car->args->t_dir_size);
	copy_carriage(core, car, val);
	get_step(car, car->args);
	printf("lfork\n");
}
