/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op03_st.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolopov <asolopov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 15:02:59 by jnovotny          #+#    #+#             */
/*   Updated: 2020/07/20 20:12:43 by asolopov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "oplist_cw.h"

static void	process_tind(t_car *car, uint8_t *code, uint8_t *start, int arg1)
{
	int		arg2;
	uint8_t	*address;

	arg2 = decode(code, TIND_BYTE);
	arg2 = arg2 % IDX_MOD;
	address = start + arg2 % IDX_MOD;
	write_bytes(address, 4, arg1);

}

static void	process_treg(t_car *car, uint8_t *code, int source)
{
	int	target;

	target = decode(code, TREG_BYTE);
	car->reg[target] = car->reg[source];
}

void		op_st(t_vm *core, t_car *car)
{
	uint8_t *code;
	uint8_t	*start;
	
	if (LOG)
		vm_log("Carriage[%zu] - operation \"%s\"\n", car->id, g_oplist[car->op_index].opname);
	fill_args("st", car->args);
	code = core->arena + car->op_index;
	start = code;
	if (!read_arg_type(car->args, (code + OP_BYTE)[0]))
	{
		get_jump(car, car->args);
		return ;
	}
	code = code + OP_BYTE + ARGTYPE_BYTE;
	car->args->arg[0] = decode(code, TREG_BYTE);
	if (car->args->arg_types[1] == T_REG)
		process_treg(car, code + TREG_BYTE, car->args->arg[0]);
	else if (car->args->arg_types[1] == T_IND)
		process_tind(car, code + TREG_BYTE, start, car->args->arg[0]);
	get_jump(car, car->args);
}
