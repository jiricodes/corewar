/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op11_sti.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolopov <asolopov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 15:02:59 by jnovotny          #+#    #+#             */
/*   Updated: 2020/07/23 14:07:03 by asolopov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "oplist_cw.h"

static void	do_sti(t_args *args, uint8_t *code, t_car *car, t_vm *core)
{
	int	val[3];

	val[0] = car->reg[args->arg[0] - 1];
	if (args->arg_types[1] == T_IND)
		val[1] = get_tind(args->arg[1], code);
	else if (args->arg_types[1] == T_DIR)
		val[1] = args->arg[1];
	else if (args->arg_types[1] == T_REG)
		val[1] = car->reg[args->arg[1] - 1];
	if (args->arg_types[2] == T_REG)
		val[2] = car->reg[args->arg[2] - 1];
	else if (args->arg_types[2] == T_DIR)
		val[2] = args->arg[2];
	write_bytes(car->pc + (val[1] + val[2]) % IDX_MOD, val[0], car, core);
}

void		op_sti(t_vm *core, t_car *car)
{
	uint8_t	*code;
	
	if (LOG)
		vm_log("Carriage[%zu] - operation \"%s\"\n", car->id, g_oplist[car->op_index].opname);
	fill_args("sti", car->args);
	code = core->arena + car->pc;
	if (read_arg_type(car->args, (code + OP_BYTE)[0]))
	{
		read_args(code + OP_BYTE + ARGTYPE_BYTE, car->args);
		do_sti(car->args, code, car, core);
	}
	get_step(car, car->args);
	printf("sti\n");
}
