/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_bytecode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolopov <asolopov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 12:05:11 by asolopov          #+#    #+#             */
/*   Updated: 2020/06/30 13:58:40 by asolopov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <stdio.h>

int	swap_int16(int val)
{
	return ((val & 0x00FF) << 8 | (val & 0xFF00) >> 8);
}

int	swap_int32(int val)
{
	return ((val & 0xFF000000) >> 24 | (val & 0x00FF0000) >> 8 |
	(val & 0x0000FF00) << 8 | (val & 0x000000FF) << 24);
}

int	negative_to_hex(int	orig)
{
	int new;

	new = 0;
	new += (orig * -1);
	new = ~new + 1;
	return (new);
}

int	get_arg_code(t_operation *operation)
{
	int cnt;
	int shift;
	int	ret;

	cnt = 0;
	shift = 6;
	ret = 0b00000000;
	while (cnt < 3)
	{
		if (operation->argtypes[cnt] == T_REG)
			ret += T_REG_CODE << shift;
		else if (operation->argtypes[cnt] == T_DIR)
			ret += T_DIR_CODE << shift;
		else if (operation->argtypes[cnt] == T_IND)
			ret += T_IND_CODE << shift;
		shift -= 2;
		cnt += 1;
	}
	return (ret);
}

int	write_args_to_bytecode(t_operation *op, int fd)
{
	int cnt;
	int	temp;

	cnt = 0;
	while (cnt < 3)
	{
		if (op->argtypes[cnt] == T_REG)
		{
			temp = ft_atoi(op->arg[cnt] + 1);
			write(fd, &temp, 1);
		}
		else if (op->argtypes[cnt] == T_DIR)
		{
			if (op->arg[cnt][1] == ':')
			{
				temp = op->label_pos[cnt];
				if (op->t_dir_size == 2)
				{
					temp = swap_int16(temp);
					write(fd, &temp, 2);
				}
				else if (op->t_dir_size == 4)
				{
					temp = swap_int32(temp);
					write(fd, &temp, 4);
				}
			}
			else
			{
				temp = ft_atoi(op->arg[cnt] + 1);
				if (op->t_dir_size == 2)
				{
					temp = swap_int16(temp);
					write(fd, &temp, 2);
				}
				else if (op->t_dir_size == 4)
				{
					temp = swap_int32(temp);
					write(fd, &temp, 4);
				}
			}
		}
		else if (op->argtypes[cnt] == T_IND)
		{
			temp = ft_atoi(op->arg[cnt]);
			temp = swap_int16(temp);
			write(fd, &temp, 2);
		}
		cnt += 1;
	}
}

void	write_magic(int fd)
{
	int magic;

	magic = COREWAR_EXEC_MAGIC;
	magic = swap_int32(magic);
	write(fd, &magic, 4);
}

void	test_operation(t_asm *core, t_operation *op)
{
	int ret;
	int fd;
	int	arg_code;
	int cnt;
	int temp;
	t_operation *cpy;

	cpy = op;
	fd = core->core_fd;
	write_magic(fd);
	while (cpy)
	{
		cnt = 0;
		if (cpy->op_code != 0)
		{
			write(fd, &cpy->op_code, 1);
			arg_code = get_arg_code(cpy);
			if (cpy->arg_type_code)
				write(fd, &arg_code, 1);
			write_args_to_bytecode(cpy, fd);
		}
		cpy = cpy->next;
	}
}
