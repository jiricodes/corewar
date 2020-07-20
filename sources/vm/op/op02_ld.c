/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op02_ld.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolopov <asolopov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 15:02:59 by jnovotny          #+#    #+#             */
/*   Updated: 2020/07/20 20:19:58 by asolopov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "oplist_cw.h"

static void	process_tdir(t_car *car, t_args *args, uint8_t *code, uint8_t *start)
{
	args->arg[0] = decode(code, args->t_dir_size);
	args->arg[1] = decode(code + args->t_dir_size, TREG_BYTE);
	car->reg[args->arg[1]] = decode(start + args->arg[0], REGSIZE);
	car->carry = (car->reg[args->arg[1]]) ? 0 : 1;
}

static void	process_tind(t_car *car, t_args *args, uint8_t *code, uint8_t *start)
{
	args->arg[0] = decode(code, TIND_BYTE);
	args->arg[1] = decode(code + TIND_BYTE, TREG_BYTE);
	car->reg[args->arg[1]] = decode(start + args->arg[0], REGSIZE) % IDX_MOD;
	car->carry = (car->reg[args->arg[1]]) ? 0 : 1;
}

void		op_ld(t_vm *core, t_car *car)
{
	uint8_t	*code;
	uint8_t	*start;

	if (LOG)
		vm_log("Carriage[%zu] - operation \"%s\"\n", car->id, g_oplist[car->op_index].opname);
	fill_args("ld", car->args);
	code = core->arena + car->op_index;
	start = core->arena + car->op_index;
	if (!read_arg_type(car->args, (code + OP_BYTE)[0]))
	{
		get_jump(car, car->args);
		return ;
	}
	code = code + OP_BYTE + ARGTYPE_BYTE;
	if (car->args->arg_types[0] == T_DIR)
		process_tdir(car, car->args, code, start);
	else if (car->args->arg_types[0] == T_IND)
		process_tind(car, car->args, code, start);
	get_jump(car, car->args);
}
