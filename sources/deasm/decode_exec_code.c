/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decode_exec_code.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolopov <asolopov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 16:15:07 by asolopov          #+#    #+#             */
/*   Updated: 2020/07/13 17:37:36 by asolopov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "deasm.h"

void	read_opcode(int8_t byte, t_operation *op)
{
	int cnt;

	cnt = 0;
	while (cnt < 16)
	{
		if (byte == oplist[cnt].opcode)
		{
			op->opname = oplist[cnt].opname;
			op->arg_type_code = oplist[cnt].arg_type_code;
			op->t_dir_size = oplist[cnt].t_dir_size;
		}
		cnt += 1;
	}
	printf("\nname: %s\n", op->opname);
	printf("argtypecode: %d\n", op->arg_type_code);
	printf("t_dir_size: %d\n", op->t_dir_size);
}

void	read_arg_type_code(int8_t byte, t_operation *op)
{
	op->argtypes[0] = (byte & 0b11000000) >> 6;
	op->argtypes[1] = (byte & 0b00110000) >> 4;
	op->argtypes[2] = (byte & 0b00001100) >> 2;
	printf("argtype 0: %d\n", op->argtypes[0]);
	printf("argtype 1: %d\n", op->argtypes[1]);
	printf("argtype 2: %d\n", op->argtypes[2]);
}

void	get_arg_type_code(t_operation *op)
{
	int cnt;

	cnt = 0;
	while (cnt < 16)
	{
		if (op->opname == oplist[cnt].opname)
		{
			op->argtypes[0] = oplist[cnt].arg_type[0];
			op->argtypes[1] = oplist[cnt].arg_type[1];
			op->argtypes[2] = oplist[cnt].arg_type[2];
		}
		cnt += 1;
	}
}

int		read_arguments(int8_t *rawcode, int start, t_operation *op)
{
	int move;
	int cnt;
	int jump;
	int32_t val;

	cnt = 0;
	move = start;
	while (cnt < 3)
	{
		if (op->argtypes[cnt] == T_REG_CODE)
		{
			jump = 1;
			val = decode((uint8_t *)(rawcode + move), jump);
		}
		else if (op->argtypes[cnt] == T_DIR_CODE)
		{
			jump = op->t_dir_size;
			val = decode((uint8_t *)(rawcode + move), jump);
		}
		else if (op->argtypes[cnt] == T_IND_CODE)
		{
			jump = 2;
			val = decode((uint8_t *)(rawcode + move), jump);
		}
		printf("%d\n", val);
		cnt += 1;
		move += jump;
	}
}

void	decode_exec_code(t_deasm *core, int8_t *rawcode)
{
	int			cnt;
	int			val;
	t_operation *op;

	op = (t_operation *)malloc(sizeof(t_operation));

	cnt = 0;
	while (cnt < core->exec_code_size)
	{
		read_opcode(rawcode[cnt], op);
		cnt += 1;
		if (op->arg_type_code == 1)
		{
			read_arg_type_code(rawcode[cnt], op);
			cnt += 1;
		}
		else
			get_arg_type_code(op);
		val = read_arguments(rawcode, cnt, op);
		cnt += val;
	}
}
