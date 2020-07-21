/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op11_sti.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolopov <asolopov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 15:02:59 by jnovotny          #+#    #+#             */
/*   Updated: 2020/07/21 21:34:36 by asolopov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "oplist_cw.h"

static void	process_treg(t_car *car, t_args *args, int arg0, uint8_t *start)
{
	int		val0;
	int		val1;
	int		val2;
	uint8_t	*code;

	val0 = car->reg[arg0];
	code = start + car->pc + OP_BYTE + ARGTYPE_BYTE + TREG_BYTE;
	car->args->arg[1] = decode(code, TREG_BYTE);
	val1 = car->reg[car->args->arg[1]];
	if (args->arg_types[2] == T_REG)
	{
		car->args->arg[2] = decode(code + TREG_BYTE, TREG_BYTE);
		val2 = car->reg[car->args->arg[2]];
	}
	else if (args->arg_types[2] == T_DIR)
		val2 = decode(code + TREG_BYTE, car->args->t_dir_size);
	write_bytes(start + (val1 + val2) % IDX_MOD, REGSIZE, car->reg[val0]);
}

static void	process_tdir(t_car *car, t_args *args, int arg0, uint8_t *start)
{
	int		val0;
	int		val1;
	int		val2;
	uint8_t	*code;

	val0 = car->reg[arg0 - 1]; // does it need * -1?
	code = start + car->pc + OP_BYTE + ARGTYPE_BYTE + TREG_BYTE;
	val1 = decode(code, args->t_dir_size);
	if (args->arg_types[2] == T_REG)
	{
		args->arg[2] = decode(code + args->t_dir_size, TREG_BYTE);
		val2 = car->reg[args->arg[2]];
	}
	else if (args->arg_types[2] == T_DIR)
	{
		val2 = decode(code + args->t_dir_size, args->t_dir_size);
		// printf("%d ", val0);
		// printf("%d ", val1);
		// printf("%d\n", val2);
	}
	write_bytes(start + (val1 + val2) % IDX_MOD, REGSIZE, val0);
}

static void	process_tind(t_car *car, t_args *args, int arg0, uint8_t *start)
{
	int		val0;
	int		val1;
	int		val2;
	uint8_t	*code;

	val0 = car->reg[arg0];
	code = start + car->pc + OP_BYTE + ARGTYPE_BYTE + TREG_BYTE;
	args->arg[1] = decode(code, TIND_BYTE);
	val1 = decode(code + args->arg[1] % IDX_MOD, REGSIZE);
	if (args->arg_types[2] == T_REG)
	{
		args->arg[2] = decode(code + TIND_BYTE, TREG_BYTE);
		val2 = car->reg[args->arg[2]];
	}
	else if (args->arg_types[2] == T_DIR)
		val2 = decode(code + TIND_BYTE, args->t_dir_size);
	write_bytes(start + (val1 + val2) % IDX_MOD, REGSIZE, car->reg[val0]);
}

void		op_sti(t_vm *core, t_car *car)
{
	uint8_t *code;
	uint8_t	*start;
	
	if (LOG)
		vm_log("Carriage[%zu] - operation \"%s\"\n", car->id, g_oplist[car->op_index].opname);
	fill_args("sti", car->args);
	code = core->arena + car->pc;
	start = code;
	if (!read_arg_type(car->args, code[1]))
	{
		get_jump(car, car->args);
		printf("bad args sti!\n");
		return ;
	}
	code = code + OP_BYTE + ARGTYPE_BYTE;
	car->args->arg[0] = decode(code, TREG_BYTE);
	if (car->args->arg_types[1] == T_DIR)
		process_tdir(car, car->args, car->args->arg[0], start);
	else if (car->args->arg_types[1] == T_IND)
		process_tind(car, car->args, car->args->arg[0], start);
	else if (car->args->arg_types[1] == T_REG)
		process_treg(car, car->args, car->args->arg[0], start);
	get_jump(car, car->args);
	printf("sti\n");
}
