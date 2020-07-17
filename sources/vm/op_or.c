/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_or.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolopov <asolopov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 14:29:12 by asolopov          #+#    #+#             */
/*   Updated: 2020/07/17 14:30:02 by asolopov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	read_args(int8_t *rawcode, t_args *args)
{
	int	cnt;
	int	step;
	int	temp;
	int	code;

	cnt = 0;
	step = 0;
	code = rawcode;
	while (cnt < 4)
	{
		if (args->arg_types[cnt] == T_REG)
		{
			args->arg[cnt] = decode((uint8_t *)code, TREG_BYTE);
			step = TREG_BYTE;
		}
		else if (args->arg_types[cnt] == T_DIR)
		{
			args->arg[cnt] = decode((uint8_t *)code, args->t_dir_size);
			step = args->t_dir_size;
		}
		else if (args->arg_types[cnt] == T_IND)
		{
			temp = decode((uint8_t *)code, TIND_BYTE);
			args->arg[cnt] = decode((uint8_t *)(rawcode + temp), REGSIZE) % IDX_MOD;
			step = TIND_BYTE;
		}
		cnt += 1;
		code += step;
	}
}

void	op_or(int8_t *rawcode, t_car *car)
{

	t_args	*args;
	int8_t	*code;

	args = init_args("or");
	code = rawcode;
	if (!read_arg_type(args, (code + OP_BYTE)[0]))
	{
		get_jump(car, args);
		return ;
	}
	code = rawcode + OP_BYTE + ARGTYPE_BYTE;
	read_args(code, args);
	car->reg[args->arg[2]] = args->arg[0] | args->arg[1];
	car->carry = (car->reg[args->arg[2]]) ? 0 : 1;
	get_jump(car, args);
	free(args);
}
