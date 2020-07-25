/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolopov <asolopov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 17:24:38 by asolopov          #+#    #+#             */
/*   Updated: 2020/07/25 21:09:39 by asolopov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "oplist_cw.h"

static int	check_types(int *types, const int *reference)
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

int		read_args(uint8_t *arena, t_args *args, ssize_t index)
{
	int		cnt;

	cnt = 0;
	while (cnt < 3)
	{
		if (args->arg_types[cnt] == T_REG)
		{
			args->arg[cnt] = read_arena(arena, index % MEM_SIZE, 0, TREG_SIZE);
			if (args->arg[cnt] > 16 || args->arg[cnt] < 1)
				return (0);
			index += TREG_SIZE;
		}
		else if (args->arg_types[cnt] == T_DIR)
		{
			args->arg[cnt] = read_arena(arena, index % MEM_SIZE, 0, args->t_dir_size);
			index += args->t_dir_size;
		}
		else if (args->arg_types[cnt] == T_IND)
		{
			args->arg[cnt] = read_arena(arena, index % MEM_SIZE, 0, 2);
			index += 2;
		}
		cnt += 1;
	}
	return (1);
}