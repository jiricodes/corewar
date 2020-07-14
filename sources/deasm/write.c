/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolopov <asolopov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 12:22:28 by asolopov          #+#    #+#             */
/*   Updated: 2020/07/14 15:23:38 by asolopov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "deasm.h"

/*
** strjoin .name and .comment and write to target_fd
*/

static void	write_str(int target_fd, char *src, char *base)
{
	char	*temp1;
	char	*temp2;

	temp1 = ft_strjoin("\"", src);
	temp2 = ft_strjoin(temp1, "\"\n");
	free(temp1);
	temp1 = ft_strjoin(base, temp2);
	write(target_fd, temp1, ft_strlen(temp1));
	free(temp1);
	free(temp2);
}

/*
** func to write header (name and comment) to target_fd
*/

void		write_header(int target_fd, t_deasm *core)
{
	write_str(target_fd, core->champ_name, ".name ");
	write_str(target_fd, core->champ_comment, ".comment ");
	write(target_fd, "\n", 1);
}

/*
** func to write operation to target_fd
** from struct writes:
**		opname
**		cycles through args, depending from argtype does appropriate strjoin
** frees struct before next operation
*/

void		write_op(int target_fd, t_operation *op)
{
	int		cnt;
	char	*temp;

	cnt = -1;
	write(target_fd, op->opname, ft_strlen(op->opname));
	write(target_fd, " ", 1);
	while (cnt++ < 3)
	{
		if (op->arg[cnt])
		{
			if (op->argtypes[cnt] == T_REG_CODE)
				temp = ft_strjoin("r", op->arg[cnt]);
			else if (op->argtypes[cnt] == T_DIR_CODE)
				temp = ft_strjoin("%", op->arg[cnt]);
			else if (op->argtypes[cnt] == T_IND_CODE)
				temp = ft_strdup(op->arg[cnt]);
			write(target_fd, temp, ft_strlen(temp));
			free(temp);
			free(op->arg[cnt]);
			if (op->arg[cnt + 1])
				write(target_fd, ", ", 2);
		}
	}
	write(target_fd, "\n", 1);
	free(op);
}
