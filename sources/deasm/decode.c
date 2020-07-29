/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decode.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolopov <asolopov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 16:15:07 by asolopov          #+#    #+#             */
/*   Updated: 2020/07/29 15:23:18 by asolopov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "deasm.h"

/*
** get operation code from g_oplist
*/

static void	read_opcode(int8_t byte, t_operation *op)
{
	int cnt;

	cnt = 0;
	while (cnt < 16)
	{
		if (byte == g_oplist[cnt].opcode)
		{
			op->opname = g_oplist[cnt].opname;
			op->arg_type_code = g_oplist[cnt].arg_type_code;
			op->t_dir_size = g_oplist[cnt].t_dir_size;
			return ;
		}
		cnt += 1;
	}
	ft_error_exit("no matching op found, exit", 0, 0);
}

/*
** decode arg_type_code to get arg codes
*/

static void	read_arg_type(int8_t byte, t_operation *op)
{
	op->argtypes[0] = (byte & 0b11000000) >> 6;
	op->argtypes[1] = (byte & 0b00110000) >> 4;
	op->argtypes[2] = (byte & 0b00001100) >> 2;
}

/*
** if no arg_type_code in op, get them from g_oplist
*/

static void	get_arg_type(t_operation *op)
{
	int cnt;

	cnt = 0;
	while (cnt < 16)
	{
		if (op->opname == g_oplist[cnt].opname)
		{
			op->argtypes[0] = g_oplist[cnt].arg_type[0];
			op->argtypes[1] = g_oplist[cnt].arg_type[1];
			op->argtypes[2] = g_oplist[cnt].arg_type[2];
			break ;
		}
		cnt += 1;
	}
	if (cnt == 16)
		ft_error_exit("no matching op found, exit", 0, 0);
}

/*
** func to retrieve arguments from opcode
*/

static int	read_arguments(int8_t *rawcode, t_operation *op)
{
	int move;
	int cnt;
	int jump;

	cnt = 0;
	move = 0;
	while (cnt < 3)
	{
		if (op->argtypes[cnt])
			jump = decode_arg(op, cnt, rawcode, move);
		else
			break ;
		cnt += 1;
		move += jump;
	}
	return (move);
}

/*
** func to decode opcode and write header and opcode to .s
** cnt passes through int array:
**			reading opcode
**			getting argtype (from code or oplist)
**			reading arguments from int array
** when single operation data in struct: writes to target_fd
*/

void		decode_exec(t_deasm *core, int8_t *rawcode)
{
	int			cnt;
	int			val;
	t_operation *op;

	cnt = 0;
	write_header(core->target_fd, core);
	while (cnt < core->exec_code_size)
	{
		op = init_op(op);
		read_opcode(rawcode[cnt], op);
		cnt += 1;
		if (op->arg_type_code == 1)
		{
			read_arg_type(rawcode[cnt], op);
			cnt += 1;
		}
		else
			get_arg_type(op);
		cnt += read_arguments(rawcode + cnt, op);
		write_op(core->target_fd, op);
	}
}
