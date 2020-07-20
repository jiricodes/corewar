/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op05_sub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolopov <asolopov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 15:02:59 by jnovotny          #+#    #+#             */
/*   Updated: 2020/07/20 16:58:40 by asolopov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "oplist_cw.h"

void	op_sub(t_vm *core, t_car *car)
{
	int		cnt;
	t_args	*args;
	uint8_t	*code;

	if (LOG)
		vm_log("Carriage[%zu] - operation \"%s\"\n", car->id, g_oplist[car->op_index].opname);
	args = init_args("sub");
	code = core->arena + car->op_index;
	if (!read_arg_type(args, (code + OP_BYTE)[0]))
	{
		get_jump(car, args);
		return ;
	}
	code = code + OP_BYTE + ARGTYPE_BYTE;
	cnt = 0;
	while (cnt < 4)
	{
		args->arg[cnt] = decode((uint8_t *)code, TREG_BYTE);
		code += TREG_BYTE;
		cnt += 1;
	}
	car->reg[args->arg[2]] = car->reg[args->arg[0]] - car->reg[args->arg[1]];
	car->carry = (car->reg[args->arg[1]]) ? 0 : 1;
	get_jump(car, args);
	free(args);
}