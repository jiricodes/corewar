/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op16_aff.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolopov <asolopov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 15:02:59 by jnovotny          #+#    #+#             */
/*   Updated: 2020/07/21 20:48:58 by asolopov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "oplist_cw.h"

void	op_aff(t_vm *core, t_car *car)
{
	uint8_t	*code;
	int		val;
	
	if (LOG)
		vm_log("Carriage[%zu] - operation \"%s\"\n", car->id, g_oplist[car->op_index].opname);
	fill_args("aff", car->args);
	code = core->arena + car->pc;
	car->args->arg[0] = decode(code + OP_BYTE, TREG_BYTE);
	val = (char)(car->reg[car->args->arg[0]]);
	// if flag a
	ft_putchar(val);
	get_jump(car, car->args);
	printf("aff\n");
}
