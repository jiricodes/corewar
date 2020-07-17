/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_sub.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolopov <asolopov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 14:14:34 by asolopov          #+#    #+#             */
/*   Updated: 2020/07/17 14:15:01 by asolopov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	op_sub(int8_t *rawcode, t_car *car)
{
	int		cnt;
	t_args	*args;
	int8_t	*code;

	args = init_args("sub");
	code = rawcode;
	if (!read_arg_type(args, (code + OP_BYTE)[0]))
	{
		get_jump(car, args);
		return ;
	}
	code = rawcode + OP_BYTE + ARGTYPE_BYTE;
	cnt = 0;
	while (cnt < 4)
	{
		args->arg[cnt] = decode((uint8_t *)code, TREG_BYTE);
		code += TREG_BYTE;
	}
	car->reg[args->arg[2]] = car->reg[args->arg[0]] - car->reg[args->arg[1]];
	car->carry = (car->reg[args->arg[1]]) ? 0 : 1;
	get_jump(car, args);
	free(args);
}
