/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op13_lld.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolopov <asolopov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 15:02:59 by jnovotny          #+#    #+#             */
/*   Updated: 2020/07/23 14:06:58 by asolopov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "oplist_cw.h"

static void	do_lld(t_args *args, uint8_t *code, t_car *car)
{
	int	val[2];

	if (args->arg_types[0] == T_DIR)
		val[0] = args->arg[0];
	else if (args->arg_types[0] == T_IND)
		get_tind(args->arg[0], code);
	val[1] = args->arg[1] - 1;
	car->reg[val[1]] = val[0];
	car->carry = (car->reg[val[1]]) ? 0 : 1;
}

void		op_lld(t_vm *core, t_car *car)
{
	uint8_t	*code;

	if (LOG)
		vm_log("Carriage[%zu] - operation \"%s\"\n", car->id, g_oplist[car->op_index].opname);
	fill_args("lld", car->args);
	code = core->arena + car->pc;
	if (read_arg_type(car->args, (code + OP_BYTE)[0]))
	{
		read_args(code + OP_BYTE + ARGTYPE_BYTE, car->args);
		do_lld(car->args, code, car);
	}
	get_step(car, car->args);
	printf("lld\n");
}
