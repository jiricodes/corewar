/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_bytecode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolopov <asolopov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 12:05:11 by asolopov          #+#    #+#             */
/*   Updated: 2020/06/25 16:11:42 by asolopov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <stdio.h>

int	negative_to_hex(int	orig)
{
	int new;

	new = 0;
	new += (orig * -1);
	new = ~new + 1;
	printf("%02x\n", new);
}

int	get_arg_code(t_operation *operation)
{
	int cnt;
	int shift;
	int	ret;

	cnt = 0;
	shift = 6;
	ret = 0b00000000;
	while (cnt < 3)
	{
		if (operation->argtypes[cnt] == T_REG)
			ret += T_REG_CODE << shift;
		else if (operation->argtypes[cnt] == T_DIR)
			ret += T_DIR_CODE << shift;
		else if (operation->argtypes[cnt] == T_IND)
			ret += T_IND_CODE << shift;
		shift -= 2;
		cnt += 1;
	}
	return ret;
}

void	args_to_bytecode(t_operation *op)
{
	int cnt;
	int	temp;

	cnt = 0;
	while (cnt < 3)
	{
		if (op->argtypes[cnt] == T_REG)
		{
			temp = ft_atoi(op->arg[cnt] + 1);
			printf("\tARG %d: %#04x\n", cnt, temp);
		}
		else if (op->argtypes[cnt] == T_DIR)
		{
			temp = ft_atoi(op->arg[cnt] + 1);
			printf("\tARG %d: %#06x\n", cnt, temp);
		}
		cnt += 1;
	}
}

void	test_operation(t_operation *op)
{
	int ret;
	t_operation *cpy;

	cpy = op;
	while (cpy)
	{
		printf("OPNAME: %s\n", cpy->op_name);
		printf("OPCODE:\t\t%02x\n", cpy->op_code);
		if (cpy->arg_type_code)
		{
			ret = get_arg_code(cpy);
			printf("ARG_CODE:\t%2x\n", ret);
		}
		args_to_bytecode(cpy);
		printf("\n");
		cpy = cpy->next;
	}
	negative_to_hex(-19);
}