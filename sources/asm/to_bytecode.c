/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_bytecode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolopov <asolopov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 12:05:11 by asolopov          #+#    #+#             */
/*   Updated: 2020/06/25 12:47:13 by asolopov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

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


test_operation(t_operation *op)
{
	int ret;

	while (op->next)
	{
		if (op->arg_type_code)
			ret = get_arg_code(op);
		printf("\n\n\n%d\n", ret);
		op = op->next;
	}

}