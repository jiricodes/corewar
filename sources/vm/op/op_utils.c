/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolopov <asolopov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 12:48:25 by asolopov          #+#    #+#             */
/*   Updated: 2020/08/03 19:55:11 by asolopov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "oplist_cw.h"

void	write_bytes(size_t index, int val, t_car *car, t_vm *core)
{
	int		x;
	int		size;
	uint8_t	byte;
	int		pos;

	x = 0;
	size = 4;
	while (size)
	{
		byte = (uint8_t)(val >> x) & 0xFF;
		pos = mod(index + size - 1, MEM_SIZE);
		core->arena[pos] = byte;
		core->byte_owner[pos] = core->byte_owner[car->pc];
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
	while (cnt < args->arg_cnt)
	{
		if (args->arg_types[cnt] == T_REG)
			val += TREG_SIZE;
		if (args->arg_types[cnt] == T_IND)
			val += IND_SIZE;
		if (args->arg_types[cnt] == T_DIR)
			val += args->dir_size;
		cnt += 1;
	}
	car->step = val;
}

void	copy_carriage(t_vm *core, t_car *car, int addr)
{
	t_car	*new;
	int		cnt;

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
	core->car_list = prepend_carriage(core->car_list, new);
}

int mod(int a, int b)
{
    int r = a % b;
    return r < 0 ? r + b : r;
}