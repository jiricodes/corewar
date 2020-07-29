/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 17:24:38 by asolopov          #+#    #+#             */
/*   Updated: 2020/07/29 18:27:25 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "oplist_cw.h"

static int	check_types(int *types, const int *reference)
{
	int cnt;

	cnt = 0;
	while (cnt < 3)
	{
		if ((!types[cnt] && reference[cnt]) ||\
			((types[cnt] | reference[cnt]) != reference[cnt]))
			return (0);
		cnt += 1;
	}
	return (1);
}

int			read_arg_type(uint8_t *arena, t_args *args, ssize_t index)
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

static int	t_reg_arg(t_vm *core, t_args *args, ssize_t *pos, int x)
{
	args->arg[x] = read_arena(core->arena, *pos % MEM_SIZE,\
		0, TREG_SIZE);
	if (args->arg[x] > 16 || args->arg[x] < 1)
		return (0);
	*pos += TREG_SIZE;
	return (1);
}

int			read_args(t_vm *core, t_args *args, ssize_t pos)
{
	int		x;

	x = 0;
	while (x < args->arg_cnt)
	{
		if (args->arg_types[x] == T_REG)
		{
			if (!t_reg_arg(core, args, &pos, x))
				return (0);
		}
		else if (args->arg_types[x] == T_DIR)
		{
			args->arg[x] = read_arena(core->arena, pos % MEM_SIZE,\
				0, args->dir_size);
			pos += args->dir_size;
		}
		else if (args->arg_types[x] == T_IND)
		{
			args->arg[x] = read_arena(core->arena, pos % MEM_SIZE, 0, 2);
			pos += 2;
		}
		x += 1;
	}
	return (1);
}
