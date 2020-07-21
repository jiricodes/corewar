/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op10_ldi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolopov <asolopov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 15:02:59 by jnovotny          #+#    #+#             */
/*   Updated: 2020/07/21 20:48:28 by asolopov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "oplist_cw.h"

static void	process_treg(t_car *car, t_args *args, uint8_t *code, uint8_t *start)
{
	args->arg[0] = decode(code, TREG_BYTE);
	if (args->arg_types[1] == T_REG)
	{
		args->arg[1] = decode(code + TREG_BYTE, TREG_BYTE);
		args->arg[2] = decode(code + TREG_BYTE + TREG_BYTE, TREG_BYTE);
	}
	else if (args->arg_types[1] == T_DIR)
	{
		args->arg[1] = decode(code + TREG_BYTE, args->t_dir_size);
		args->arg[2] = decode(code + TREG_BYTE + args->t_dir_size, TREG_BYTE);
	}
	car->reg[args->arg[2]] = decode(start + (args->arg[0] + args->arg[1]) % IDX_MOD, REGSIZE);

}

static void	process_tdir(t_car *car, t_args *args, uint8_t *code, uint8_t *start)
{
	args->arg[0] = decode(code, args->t_dir_size);
	if (args->arg_types[1] == T_REG)
	{
		args->arg[1] = decode(code + args->t_dir_size, TREG_BYTE);
		args->arg[2] = decode(code + args->t_dir_size + TREG_BYTE, TREG_BYTE);
	}
	else if (args->arg_types[1] == T_DIR)
	{
		args->arg[1] = decode(code + args->t_dir_size, args->t_dir_size);
		args->arg[2] = decode(code + args->t_dir_size + args->t_dir_size, TREG_BYTE);
	}
	car->reg[args->arg[2]] = decode(start + (args->arg[0] + args->arg[1]) % IDX_MOD, REGSIZE);
}

static void	process_tind(t_car *car, t_args *args, uint8_t *code, uint8_t *start)
{
	args->arg[0] = decode(code, TIND_BYTE);
	args->arg[0] = decode(code + args->arg[0] % IDX_MOD, REGSIZE);
	if (args->arg_types[1] == T_REG)
	{
		args->arg[1] = decode(code + TIND_BYTE, TREG_BYTE);
		args->arg[2] = decode(code + TIND_BYTE + TREG_BYTE, TREG_BYTE);
	}
	else if (args->arg_types[1] == T_DIR)
	{
		args->arg[1] = decode(code + TIND_BYTE, args->t_dir_size);
		args->arg[2] = decode(code + TIND_BYTE + args->t_dir_size, TREG_BYTE);
	}
	car->reg[args->arg[2]] = decode(start + (args->arg[0] + args->arg[1]) % IDX_MOD, REGSIZE);
}

void		op_ldi(t_vm *core, t_car *car)
{
	uint8_t	*code;
	uint8_t	*start;
	
	if (LOG)
		vm_log("Carriage[%zu] - operation \"%s\"\n", car->id, g_oplist[car->op_index].opname);
	fill_args("ldi", car->args);
	code = core->arena + car->pc;
	start = code;
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
	else if (car->args->arg_types[0] == T_REG)
		process_treg(car, car->args, code, start);
	get_jump(car, car->args);
	printf("ldi\n");
}
