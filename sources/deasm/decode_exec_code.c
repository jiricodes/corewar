/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decode_exec_code.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolopov <asolopov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 16:15:07 by asolopov          #+#    #+#             */
/*   Updated: 2020/07/13 19:34:12 by asolopov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "deasm.h"

void	read_opcode(int8_t byte, t_operation *op)
{
	int cnt;

	cnt = 0;
	while (cnt < 16)
	{
		if (byte == oplist[cnt].opcode)
		{
			op->opname = oplist[cnt].opname;
			op->arg_type_code = oplist[cnt].arg_type_code;
			op->t_dir_size = oplist[cnt].t_dir_size;
		}
		cnt += 1;
	}
}

void	read_arg_type_code(int8_t byte, t_operation *op)
{
	op->argtypes[0] = (byte & 0b11000000) >> 6;
	op->argtypes[1] = (byte & 0b00110000) >> 4;
	op->argtypes[2] = (byte & 0b00001100) >> 2;
}

void	get_arg_type_code(t_operation *op)
{
	int cnt;

	cnt = 0;
	while (cnt < 16)
	{
		if (op->opname == oplist[cnt].opname)
		{
			op->argtypes[0] = oplist[cnt].arg_type[0];
			op->argtypes[1] = oplist[cnt].arg_type[1];
			op->argtypes[2] = oplist[cnt].arg_type[2];
		}
		cnt += 1;
	}
}

int		read_arguments(int8_t *rawcode, t_operation *op)
{
	int move;
	int cnt;
	int jump;

	cnt = 0;
	move = 0;
	while (cnt < 3)
	{
		if (op->argtypes[cnt] == T_REG_CODE)
		{
			jump = 1;
			op->arg[cnt] = ft_itoa(decode((uint8_t *)(rawcode + move), jump));
		}
		else if (op->argtypes[cnt] == T_DIR_CODE)
		{
			jump = op->t_dir_size;
			op->arg[cnt] = ft_itoa(decode((uint8_t *)(rawcode + move), jump));
		}
		else if (op->argtypes[cnt] == T_IND_CODE)
		{
			jump = 2;
			op->arg[cnt] = ft_itoa(decode((uint8_t *)(rawcode + move), jump));
		}
		else
			break ;
		cnt += 1;
		move += jump;
	}
	return (move);
}

void	write_clear_op(int target_fd, t_operation *op)
{
	int 	cnt;
	char	*temp;

	cnt = 0;
	write(target_fd, op->opname, ft_strlen(op->opname));
	write(target_fd, " ", 1);
	while (cnt < 3)
	{
		if (op->arg[cnt])
		{
			if (op->argtypes[cnt] == T_REG_CODE)
				temp = ft_strjoin("r", op->arg[cnt]);
			else if (op->argtypes[cnt] == T_IND_CODE || op->argtypes[cnt] == T_DIR_CODE)
				temp = ft_strjoin("%", op->arg[cnt]);
			write(target_fd, temp, ft_strlen(temp));
			if (op->arg[cnt + 1])
				write(target_fd, ", ", 2);
		}
		cnt += 1;
	}
	write(target_fd, "\n", 1);
	free(op);
}

void	write_line(int target_fd, char *src)
{
	char	*temp1;
	char	*temp2;

	temp1 = ft_strjoin("\"", src);
	temp2 = ft_strjoin(temp1, "\"\n");
	free(temp1);
	temp1 = ft_strjoin(".name ", temp2);
	write(target_fd, temp1, ft_strlen(temp1));
	free(temp1);
	free(temp2);
}

void	write_header(int target_fd, t_deasm *core)
{
	write_line(target_fd, core->champ_name);
	write_line(target_fd, core->champ_comment);
	write(target_fd, "\n", 1);
}

t_operation	*init_op(t_operation *op)
{
	t_operation *new;

	new = (t_operation *)malloc(sizeof(t_operation));
	new->arg[0] = 0;
	new->arg[1] = 0;
	new->arg[2] = 0;
	new->argtypes[0] = 0;
	new->argtypes[1] = 0;
	new->argtypes[2] = 0;
	return (new);
}

void	decode_exec_code(t_deasm *core, int8_t *rawcode)
{
	int			cnt;
	int			val;
	t_operation *op;

	cnt = 0;
	write_header(core->target_fd, core);
	while (cnt < core->exec_code_size)
	{
		op = init_op(op);
		read_opcode(rawcode[cnt], op);
		cnt += 1;
		if (op->arg_type_code == 1)
		{
			read_arg_type_code(rawcode[cnt], op);
			cnt += 1;
		}
		else
			get_arg_type_code(op);
		cnt += read_arguments(rawcode + cnt, op);
		write_clear_op(core->target_fd, op);
	}
}
