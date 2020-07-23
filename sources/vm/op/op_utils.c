/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolopov <asolopov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 12:48:25 by asolopov          #+#    #+#             */
/*   Updated: 2020/07/23 19:00:07 by asolopov         ###   ########.fr       */
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

int	check_types(int *types, const int *reference)
{
	int cnt;

	cnt = 0;
	while (cnt < 3)
	{
		if ((types[cnt] | reference[cnt]) != reference[cnt])
			return (0);
		cnt += 1;
	}
	return (1);
}

int	read_arg_type(uint8_t *arena, t_args *args, ssize_t index)
{
	int byte;
	int cnt;
	int	temp[3];

	byte = arena[index];
	cnt = 0;
	temp[0] = (byte & 0b11000000) >> 6;
	temp[1] = (byte & 0b00110000) >> 4;
	temp[2] = (byte & 0b00001100) >> 2;
	while (cnt < 3)
	{
		if (temp[cnt] == TREG_CODE)
			args->arg_types[cnt] = T_REG;
		if (temp[cnt] == TIND_CODE)
			args->arg_types[cnt] = T_IND;
		if (temp[cnt] == TDIR_CODE)
			args->arg_types[cnt] = T_DIR;
		cnt += 1;
	}
	if (!check_types(args->arg_types, g_oplist[args->opcount].arg_type))
		return (0);
	else
		return (1);
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

int		read_args(uint8_t *arena, t_args *args, ssize_t index)
{
	int		cnt;

	cnt = 0;
	while (cnt < 3)
	{
		if (args->arg_types[cnt] == T_REG)
		{
			args->arg[cnt] = read_arena(arena, index, 0, TREG_SIZE);
			if (args->arg[cnt] > 16 || args->arg[cnt] < 1)
				return (0);
			index += TREG_SIZE;
		}
		else if (args->arg_types[cnt] == T_DIR)
		{
			args->arg[cnt] = read_arena(arena, index, 0, args->t_dir_size);
			index += args->t_dir_size;
		}
		else if (args->arg_types[cnt] == T_IND)
		{
			args->arg[cnt] = read_arena(arena, index, 0, 2);
			index += 2;
		}
		cnt += 1;
	}
	return (1);
}

int			read_arena(uint8_t *arena, int start, int argval, int size)
{
	int		ret;
	uint8_t	code[size];
	int		cnt;

	cnt = 0;
	while (cnt < size)
	{
		code[cnt] = arena[(start + argval + cnt) % MEM_SIZE];
		cnt += 1;
	}
	ret = decode(code, size);
	return (ret);
}