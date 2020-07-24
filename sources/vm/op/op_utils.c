/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolopov <asolopov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 12:48:25 by asolopov          #+#    #+#             */
/*   Updated: 2020/07/24 17:26:24 by asolopov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "oplist_cw.h"

void	fill_args(char *opname, t_args *args)
{
	int		cnt;

	cnt = 0;
	while (cnt < 16)
	{
		if (opname == g_oplist[cnt].opname)
		{
			args->opcount = cnt;
			args->arg_cnt = g_oplist[cnt].arg_cnt;
			args->arg_code = g_oplist[cnt].arg_type_code;
			args->t_dir_size = g_oplist[cnt].t_dir_size;
			args->arg_types[0] = g_oplist[cnt].arg_type[0];
			args->arg_types[1] = g_oplist[cnt].arg_type[1];
			args->arg_types[2] = g_oplist[cnt].arg_type[2];
		}
		cnt += 1;
	}
}

void	write_bytes(size_t index, int val, t_car *car, t_vm *core)
{
	int		x;
	int		size;
	uint8_t	byte;

	x = 0;
	size = 4;
	while (size)
	{
		byte = (uint8_t)(val >> x) & 0xFF;
		core->arena[(index + size - 1) % MEM_SIZE] = byte;
		core->byte_owner[(index + size - 1) % MEM_SIZE] = core->byte_owner[car->pc];
		x += 8;
		size -= 1;
	}
}

void	get_step(t_car *car, t_args *args)
{
	int val;
	int cnt;

	cnt = 0;
	val = OP_SIZE;
	if (args->arg_code)
		val += ARG_SIZE;
	while (cnt < 3)
	{
		if (args->arg_types[cnt] == T_REG)
			val += TREG_SIZE;
		if (args->arg_types[cnt] == T_IND)
			val += IND_SIZE;
		if (args->arg_types[cnt] == T_DIR)
			val += args->t_dir_size;
		cnt += 1;
	}
	car->step = val;
}

void	copy_carriage(t_vm *core, t_car *car, int addr)
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