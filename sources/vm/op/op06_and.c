/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op06_and.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolopov <asolopov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 15:02:59 by jnovotny          #+#    #+#             */
/*   Updated: 2020/07/20 17:24:32 by asolopov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "oplist_cw.h"

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

void	op_and(t_vm *core, t_car *car)
{
	int8_t	*code;

	if (LOG)
		vm_log("Carriage[%zu] - operation \"%s\"\n", car->id, g_oplist[car->op_index].opname);
	fill_args("and", car->args);
	code = core->arena + car->op_index;
	if (!read_arg_type(car->args, (code + OP_BYTE)[0]))
	{
		get_jump(car, car->args);
		return ;
	}
	code = code + OP_BYTE + ARGTYPE_BYTE;
	read_args(code, car->args);
	car->reg[car->args->arg[2]] = car->args->arg[0] & car->args->arg[1];
	car->carry = (car->reg[car->args->arg[2]]) ? 0 : 1;
	get_jump(car, car->args);
	free(car->args);
}
