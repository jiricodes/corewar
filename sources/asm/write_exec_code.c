/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_exec_code.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolopov <asolopov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 20:20:28 by asolopov          #+#    #+#             */
/*   Updated: 2020/06/30 21:13:22 by asolopov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** Write T_REG argument to .cor
*/

static void	write_t_reg(char *arg, int fd)
{
	int val;

	val = ft_atoi(arg + 1);
	write(fd, &val, 1);
}

/*
** Write T_DIR argument to .cor
*/

static void	write_t_dir(char *arg, int dir_size, int label_pos, int fd)
{
	int	val;

	if (arg[1] == LABEL_CHAR)
		val = label_pos;
	else
		val = ft_atoi(arg + 1);
	if (dir_size == 2)
		val = swap_int16(val);
	else if (dir_size == 4)
		val = swap_int32(val);
	write(fd, &val, dir_size);
}

/*
** Write T_IND argument to .cor
*/

static void	write_t_ind(char *arg, int label_pos, int fd)
{
	int	val;

	if (arg[0] == LABEL_CHAR)
		val = label_pos;
	else
		val = ft_atoi(arg);
	val = swap_int16(val);
	write(fd, &val, 2);
}

/*
** Cycle through arguments and write them to .cor
*/

static void	write_args_to_bytecode(t_operation *op, int fd)
{
	int cnt;

	cnt = 0;
	while (cnt < 3)
	{
		if (op->argtypes[cnt] == T_REG)
			write_t_reg(op->arg[cnt], fd);
		else if (op->argtypes[cnt] == T_DIR)
			write_t_dir(op->arg[cnt], op->t_dir_size, op->label_pos[cnt], fd);
		else if (op->argtypes[cnt] == T_IND)
			write_t_ind(op->arg[cnt], op->label_pos[cnt], fd);
		cnt += 1;
	}
}

/*
** Write champs exec code to .cor
*/

void		write_exec_code(t_asm *core, t_operation *op)
{
	t_operation	*cpy;
	int			arg_code;
	int			fd;

	cpy = op;
	fd = core->core_fd;
	while (cpy)
	{
		if (cpy->op_code)
		{
			write(fd, &cpy->op_code, 1);
			if (cpy->arg_type_code)
			{
				arg_code = get_arg_code(cpy);
				write(fd, &arg_code, 1);
			}
			write_args_to_bytecode(cpy, fd);
		}
		cpy = cpy->next;
	}
}
