/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op08_xor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolopov <asolopov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 15:02:59 by jnovotny          #+#    #+#             */
/*   Updated: 2020/07/22 12:44:53 by asolopov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "oplist_cw.h"

static void	do_xor(t_args *args, uint8_t *code, t_car *car)
{
	int	val[3];
	int cnt;

	cnt = 0;
	while (cnt < 2)
	{
		if (args->arg_types[cnt] == T_REG)
			val[cnt] = car->reg[args->arg[cnt] - 1];
		else if (args->arg_types[0] == T_IND)
			val[cnt] = get_tind(args->arg[cnt], code);
		else if (args->arg_types[0] == T_DIR)
			val[cnt] = args->arg[0];
		cnt += 1;
	}
	val[2] = args->arg[2] - 1;
	car->reg[val[2]] = val[0] ^ val[1];
	car->carry = car->reg[val[2]] ? 0 : 1;
}

void	op_xor(t_vm *core, t_car *car)
{
	uint8_t	*code;

	if (LOG)
		vm_log("Carriage[%zu] - operation \"%s\"\n", car->id, g_oplist[car->op_index].opname);
	fill_args("xor", car->args);
	code = core->arena + car->pc;
	if (read_arg_type(car->args, (code + OP_BYTE)[0]))
	{
		read_args(code + OP_BYTE + ARGTYPE_BYTE, car->args);
		do_xor(car->args, code, car);
	}
	get_jump(car, car->args);
	printf("xor\n");
}
