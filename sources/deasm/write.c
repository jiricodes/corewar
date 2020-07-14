/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolopov <asolopov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 12:22:28 by asolopov          #+#    #+#             */
/*   Updated: 2020/07/14 12:52:44 by asolopov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "deasm.h"

static void	write_name(int target_fd, char *src)
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

static void	write_comment(int target_fd, char *src)
{
	char	*temp1;
	char	*temp2;

	temp1 = ft_strjoin("\"", src);
	temp2 = ft_strjoin(temp1, "\"\n");
	free(temp1);
	temp1 = ft_strjoin(".comment ", temp2);
	write(target_fd, temp1, ft_strlen(temp1));
	free(temp1);
	free(temp2);
}

void		write_header(int target_fd, t_deasm *core)
{
	write_name(target_fd, core->champ_name);
	write_comment(target_fd, core->champ_comment);
	write(target_fd, "\n", 1);
}

void		write_op(int target_fd, t_operation *op)
{
	int		cnt;
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
			else if (op->argtypes[cnt] == T_DIR_CODE)
				temp = ft_strjoin("%", op->arg[cnt]);
			else if (op->argtypes[cnt] == T_IND_CODE)
				temp = op->arg[cnt];
			write(target_fd, temp, ft_strlen(temp));
			if (op->arg[cnt + 1])
				write(target_fd, ", ", 2);
		}
		cnt += 1;
	}
	write(target_fd, "\n", 1);
	free(op);
}
