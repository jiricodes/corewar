/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op05_sub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolopov <asolopov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 15:02:59 by jnovotny          #+#    #+#             */
/*   Updated: 2020/07/21 20:47:56 by asolopov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "oplist_cw.h"

void	op_sub(t_vm *core, t_car *car)
{
	int		cnt;
	uint8_t	*code;

	if (LOG)
		vm_log("Carriage[%zu] - operation \"%s\"\n", car->id, g_oplist[car->op_index].opname);
	fill_args("sub", car->args);
	code = core->arena + car->pc;
	if (!read_arg_type(car->args, (code + OP_BYTE)[0]))
	{
		get_jump(car, car->args);
		return ;
	}
	code = code + OP_BYTE + ARGTYPE_BYTE;
	cnt = 0;
	while (cnt < 4)
	{
		car->args->arg[cnt] = decode(code, TREG_BYTE);
		code += TREG_BYTE;
		cnt += 1;
	}
	car->reg[car->args->arg[2]] = car->reg[car->args->arg[0]] - car->reg[car->args->arg[1]];
	car->carry = (car->reg[car->args->arg[1]]) ? 0 : 1;
	get_jump(car, car->args);
	printf("sub\n");
}