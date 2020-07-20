/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 12:48:25 by asolopov          #+#    #+#             */
/*   Updated: 2020/07/20 17:45:19 by jnovotny         ###   ########.fr       */
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
			args->arg_code = g_oplist[cnt].arg_type_code;
			args->t_dir_size = g_oplist[cnt].t_dir_size;
			args->arg_types[0] = g_oplist[cnt].arg_type[0];
			args->arg_types[1] = g_oplist[cnt].arg_type[1];
			args->arg_types[2] = g_oplist[cnt].arg_type[2];
		}
		cnt += 1;
	}
}

int	check_types(int *types, const int *reference)
{
	int cnt;

	cnt = 0;
	while (cnt < 4)
	{
		if ((types[cnt] | reference[cnt]) != reference[cnt])
			return (0);
		cnt += 1;
	}
	return (1);
}

int	read_arg_type(t_args *args, int8_t byte)
{
	int cnt;
	int	temp[3];

	cnt = 0;
	temp[0] = (byte & 0b11000000) >> 6;
	temp[1] = (byte & 0b00110000) >> 4;
	temp[2] = (byte & 0b00001100) >> 2;
	while (cnt < 4)
	{
		if (temp[cnt] == T_REG_CODE)
			args->arg_types[cnt] = T_REG;
		if (temp[cnt] == T_IND_CODE)
			args->arg_types[cnt] = T_IND;
		if (temp[cnt] == T_DIR_CODE)
			args->arg_types[cnt] = T_DIR;
		cnt += 1;
	}
	if (!check_types(args->arg_types, g_oplist[args->opcount].arg_type))
		return (0);
	else
		return (1);
}

void	get_jump(t_car *car, t_args *args)
{
	int val;
	int cnt;

	cnt = 0;
	val = OP_BYTE;
	if (args->arg_code)
		val += ARGTYPE_BYTE;
	while (cnt < 4)
	{
		if (args->arg_types[cnt] == T_REG)
			val += TREG_BYTE;
		if (args->arg_types[cnt] == T_IND)
			val += TIND_BYTE;
		if (args->arg_types[cnt] == T_DIR)
			val += args->t_dir_size;
		cnt += 1;
	}
	car->step = val;
}
