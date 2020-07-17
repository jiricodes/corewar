/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolopov <asolopov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 12:48:07 by asolopov          #+#    #+#             */
/*   Updated: 2020/07/17 12:50:28 by asolopov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	op_ld(int8_t *rawcode, t_car *car)
{
	t_args	*args;
	int8_t	*code;

	args = init_args("ld");
	code = rawcode;
	if (!read_arg_type(args, (code + 1)[0]))
	{
		get_jump(car, args);
		return ;
	}
	code = rawcode + OP_BYTE + ARGTYPE_BYTE;
	if (args->arg_types[0] == T_DIR)
	{
		args->arg[0] = decode((uint8_t *)code, args->t_dir_size);
		args->arg[1] = decode((uint8_t *)code + args->t_dir_size, 1);
		car->reg[args->arg[1]] = decode((uint8_t *)(rawcode + args->arg[0]), 4);
	}
	else if (args->arg_types[0] == T_IND)
	{
		args->arg[0] = decode((uint8_t *)code, 2);
		args->arg[1] = decode((uint8_t *)code + 2, 1);
		car->reg[args->arg[1]] = decode((uint8_t *)(rawcode + args->arg[0]), 4) % IDX_MOD;
	}
	car->carry = (car->reg[args->arg[1]]) ? 0 : 1;
	get_jump(car, args);
	free(args);
}
