/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolopov <asolopov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 12:48:07 by asolopov          #+#    #+#             */
/*   Updated: 2020/07/17 13:02:04 by asolopov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	op_ld(int8_t *rawcode, t_car *car)
{
	t_args	*args;
	int8_t	*code;

	args = init_args("ld");
	code = rawcode;
	if (!read_arg_type(args, (code + OP_BYTE)[0]))
	{
		get_jump(car, args);
		return ;
	}
	code = rawcode + OP_BYTE + ARGTYPE_BYTE;
	if (args->arg_types[0] == T_DIR)
	{
		args->arg[0] = decode((uint8_t *)code, args->t_dir_size);
		args->arg[1] = decode((uint8_t *)code + args->t_dir_size, TREG_BYTE);
		car->reg[args->arg[1]] = decode((uint8_t *)(rawcode + args->arg[0]), REGSIZE);
	}
	else if (args->arg_types[0] == T_IND)
	{
		args->arg[0] = decode((uint8_t *)code, TIND_BYTE);
		args->arg[1] = decode((uint8_t *)code + TIND_BYTE, TREG_BYTE);
		car->reg[args->arg[1]] = decode((uint8_t *)(rawcode + args->arg[0]), REGSIZE) % IDX_MOD;
	}
	car->carry = (car->reg[args->arg[1]]) ? 0 : 1;
	get_jump(car, args);
	free(args);
}
