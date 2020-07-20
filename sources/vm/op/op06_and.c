/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op06_and.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolopov <asolopov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 15:02:59 by jnovotny          #+#    #+#             */
/*   Updated: 2020/07/20 20:19:06 by asolopov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "oplist_cw.h"

void	op_and(t_vm *core, t_car *car)
{
	uint8_t	*code;

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
}
