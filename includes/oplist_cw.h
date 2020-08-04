/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oplist_cw.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 14:13:21 by asolopov          #+#    #+#             */
/*   Updated: 2020/08/01 12:20:21 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPLIST_CW_H
# define OPLIST_CW_H

# include "vm.h"

# define TREG_CODE	0b00000001
# define TDIR_CODE	0b00000010
# define TIND_CODE	0b00000011

# define OP_SIZE	1
# define ARG_SIZE 	1
# define TREG_SIZE	1

/*
** Operations
*/

void			op_live(t_vm *core, t_car *car);
void			op_ld(t_vm *core, t_car *car);
void			op_st(t_vm *core, t_car *car);
void			op_add(t_vm *core, t_car *car);
void			op_sub(t_vm *core, t_car *car);
void			op_and(t_vm *core, t_car *car);
void			op_or(t_vm *core, t_car *car);
void			op_xor(t_vm *core, t_car *car);
void			op_zjmp(t_vm *core, t_car *car);
void			op_ldi(t_vm *core, t_car *car);
void			op_sti(t_vm *core, t_car *car);
void			op_fork(t_vm *core, t_car *car);
void			op_lld(t_vm *core, t_car *car);
void			op_lldi(t_vm *core, t_car *car);
void			op_lfork(t_vm *core, t_car *car);
void			op_aff(t_vm *core, t_car *car);

/*
** Utilities
*/

typedef struct	s_oplist
{
	int		opcode;
	char	*opname;
	int		arg_cnt;
	int		arg_type[3];
	int		t_dir_size;
	int		arg_type_code;
	int		carry_change;
	int		exec_cycles;
	void	(*op)(t_vm *, t_car *);
}				t_oplist;

static const	t_oplist	g_oplist[16] = {
	{
		.opcode = 0x01,
		.opname = "live",
		.arg_cnt = 1,
		.arg_type = {T_DIR, 0, 0},
		.t_dir_size = 4,
		.arg_type_code = 0,
		.carry_change = 0,
		.exec_cycles = 10,
		.op = &op_live
	},
	{
		.opcode = 0x02,
		.opname = "ld",
		.arg_cnt = 2,
		.arg_type = {T_DIR | T_IND, T_REG, 0},
		.t_dir_size = 4,
		.arg_type_code = 1,
		.carry_change = 1,
		.exec_cycles = 5,
		.op = &op_ld
	},
	{
		.opcode = 0x03,
		.opname = "st",
		.arg_cnt = 2,
		.arg_type = {T_REG, T_IND | T_REG, 0},
		.t_dir_size = 4,
		.arg_type_code = 1,
		.carry_change = 0,
		.exec_cycles = 5,
		.op = &op_st
	},
	{
		.opcode = 0x04,
		.opname = "add",
		.arg_cnt = 3,
		.arg_type = {T_REG, T_REG, T_REG},
		.t_dir_size = 4,
		.arg_type_code = 1,
		.carry_change = 1,
		.exec_cycles = 10,
		.op = &op_add
	},
	{
		.opcode = 0x05,
		.opname = "sub",
		.arg_cnt = 3,
		.arg_type = {T_REG, T_REG, T_REG},
		.t_dir_size = 4,
		.arg_type_code = 1,
		.carry_change = 1,
		.exec_cycles = 10,
		.op = &op_sub
	},
	{
		.opcode = 0x06,
		.opname = "and",
		.arg_cnt = 3,
		.arg_type = {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG},
		.t_dir_size = 4,
		.arg_type_code = 1,
		.carry_change = 1,
		.exec_cycles = 6,
		.op = &op_and
	},
	{
		.opcode = 0x07,
		.opname = "or",
		.arg_cnt = 3,
		.arg_type = {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},
		.t_dir_size = 4,
		.arg_type_code = 1,
		.carry_change = 1,
		.exec_cycles = 6,
		.op = &op_or
	},
	{
		.opcode = 0x08,
		.opname = "xor",
		.arg_cnt = 3,
		.arg_type = {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},
		.t_dir_size = 4,
		.arg_type_code = 1,
		.carry_change = 1,
		.exec_cycles = 6,
		.op = &op_xor
	},
	{
		.opcode = 0x09,
		.opname = "zjmp",
		.arg_cnt = 1,
		.arg_type = {T_DIR, 0, 0},
		.t_dir_size = 2,
		.arg_type_code = 0,
		.carry_change = 0,
		.exec_cycles = 20,
		.op = &op_zjmp
	},
	{
		.opcode = 0x0a,
		.opname = "ldi",
		.arg_cnt = 3,
		.arg_type = {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},
		.t_dir_size = 2,
		.arg_type_code = 1,
		.carry_change = 0,
		.exec_cycles = 25,
		.op = &op_ldi
	},
	{
		.opcode = 0x0b,
		.opname = "sti",
		.arg_cnt = 3,
		.arg_type = {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG},
		.t_dir_size = 2,
		.arg_type_code = 1,
		.carry_change = 0,
		.exec_cycles = 25,
		.op = &op_sti
	},
	{
		.opcode = 0x0c,
		.opname = "fork",
		.arg_cnt = 1,
		.arg_type = {T_DIR, 0, 0},
		.t_dir_size = 2,
		.arg_type_code = 0,
		.carry_change = 0,
		.exec_cycles = 800,
		.op = &op_fork
	},
	{
		.opcode = 0x0d,
		.opname = "lld",
		.arg_cnt = 2,
		.arg_type = {T_DIR | T_IND, T_REG},
		.t_dir_size = 4,
		.arg_type_code = 1,
		.carry_change = 1,
		.exec_cycles = 10,
		.op = &op_lld
	},
	{
		.opcode = 0x0e,
		.opname = "lldi",
		.arg_cnt = 3,
		.arg_type = {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},
		.t_dir_size = 2,
		.arg_type_code = 1,
		.carry_change = 1,
		.exec_cycles = 50,
		.op = &op_lldi
	},
	{
		.opcode = 0x0f,
		.opname = "lfork",
		.arg_cnt = 1,
		.arg_type = {T_DIR, 0, 0},
		.t_dir_size = 2,
		.arg_type_code = 0,
		.carry_change = 0,
		.exec_cycles = 1000,
		.op = &op_lfork
	},
	{
		.opcode = 0x10,
		.opname = "aff",
		.arg_cnt = 1,
		.arg_type = {T_REG, 0, 0},
		.t_dir_size = 4,
		.arg_type_code = 1,
		.carry_change = 0,
		.exec_cycles = 2,
		.op = &op_aff
	}
};

#endif
