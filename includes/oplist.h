/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oplist.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolopov <asolopov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 14:13:21 by asolopov          #+#    #+#             */
/*   Updated: 2020/06/25 12:37:02 by asolopov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef OPLIST_H

# define OPLIST_H

#define T_REG		1
#define T_DIR		2
#define T_IND		4
#define T_LAB		8

#define T_REG_CODE	0b00000001
#define T_DIR_CODE	0b00000010
#define	T_IND_CODE	0b00000011

typedef struct	s_oplist
{
	int		opcode;
	char	*opname;
	int		arg_cnt;
	int		arg_type[3];
	int		t_dir_size;
	int		arg_type_code;
}				t_oplist;

static const	t_oplist	oplist[16] = {
	{
		.opcode = 1,
		.opname = "live",
		.arg_cnt = 1,
		.arg_type = {T_DIR, 0, 0},
		.t_dir_size = 4,
		.arg_type_code = 0
	},
	{
		.opcode = 2,
		.opname = "ld",
		.arg_cnt = 2,
		.arg_type = {T_DIR | T_IND, T_REG, 0},
		.t_dir_size = 4,
		.arg_type_code = 1
	},
	{
		.opcode = 3,
		.opname = "st",
		.arg_cnt = 2,
		.arg_type = {T_REG, T_IND | T_REG, 0},
		.t_dir_size = 4,
		.arg_type_code = 1
	},
	{
		.opcode = 4,
		.opname = "add",
		.arg_cnt = 3,
		.arg_type = {T_REG, T_REG, T_REG},
		.t_dir_size = 4,
		.arg_type_code = 1
	},
	{
		.opcode = 5,
		.opname = "sub",
		.arg_cnt = 3,
		.arg_type = {T_REG, T_REG, T_REG},
		.t_dir_size = 4,
		.arg_type_code = 1
	},
	{
		.opcode = 6,
		.opname = "and",
		.arg_cnt = 3,
		.arg_type = {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG},
		.t_dir_size = 4,
		.arg_type_code = 1
	},
	{
		.opcode = 7,
		.opname = "or",
		.arg_cnt = 3,
		.arg_type = {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},
		.t_dir_size = 4,
		.arg_type_code = 1
	},
	{
		.opcode = 8,
		.opname = "xor",
		.arg_cnt = 3,
		.arg_type = {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},
		.t_dir_size = 4,
		.arg_type_code = 1
	},
	{
		.opcode = 9,
		.opname = "zjmp",
		.arg_cnt = 1,
		.arg_type = {T_DIR, 0, 0},
		.t_dir_size = 2,
		.arg_type_code = 0
	},
	{
		.opcode = 10,
		.opname = "ldi",
		.arg_cnt = 3,
		.arg_type = {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},
		.t_dir_size = 2,
		.arg_type_code = 1
	},
		{
		.opcode = 11,
		.opname = "sti",
		.arg_cnt = 3,
		.arg_type = {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG},
		.t_dir_size = 2,
		.arg_type_code = 1
	},
		{
		.opcode = 12,
		.opname = "fork",
		.arg_cnt = 1,
		.arg_type = {T_DIR, 0, 0},
		.t_dir_size = 2,
		.arg_type_code = 0
	},
		{
		.opcode = 13,
		.opname = "lld",
		.arg_cnt = 3,
		.arg_type = {T_DIR | T_IND, T_REG},
		.t_dir_size = 4,
		.arg_type_code = 1
	},
		{
		.opcode = 14,
		.opname = "lldi",
		.arg_cnt = 3,
		.arg_type = {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},
		.t_dir_size = 2,
		.arg_type_code = 1
	},
		{
		.opcode = 15,
		.opname = "lfork",
		.arg_cnt = 1,
		.arg_type = {T_DIR, 0, 0},
		.t_dir_size = 2,
		.arg_type_code = 0
	},
	{
		.opcode = 16,
		.opname = "aff",
		.arg_cnt = 1,
		.arg_type = {T_REG, 0, 0},
		.t_dir_size = 4,
		.arg_type_code = 0
	}
};

#endif