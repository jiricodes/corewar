/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op03_st.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolopov <asolopov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 15:02:59 by jnovotny          #+#    #+#             */
/*   Updated: 2020/07/23 12:02:02 by asolopov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "oplist_cw.h"

static void	do_st(t_args *args, uint8_t *code, t_car *car)
{
	int	val[2];
	int	temp;

	val[0] = car->reg[args->arg[0] - 1];
	if (args->arg_types[1] == T_IND)
	{
		val[1] = args->arg[1] % IDX_MOD;
		write_bytes(code + val[1] % IDX_MOD, REG_SIZE, val[0]);
	}
	else if (args->arg_types[1] == T_REG)
	{
		val[1] = args->arg[1];
		car->reg[val[1] - 1] = val[0];
	}
}

void		op_st(t_vm *core, t_car *car)
{
	uint8_t *code;

	if (LOG)
		vm_log("Carriage[%zu] - operation \"%s\"\n", car->id, g_oplist[car->op_index].opname);
	fill_args("st", car->args);
	code = core->arena + car->pc;
	if (read_arg_type(car->args, (code + OP_BYTE)[0]))
	{
		read_args(code + OP_BYTE + ARGTYPE_BYTE, car->args);
		do_st(car->args, code, car);
	}
	get_jump(car, car->args);
	printf("st\n");
}

