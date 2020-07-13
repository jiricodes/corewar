/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 20:18:47 by asolopov          #+#    #+#             */
/*   Updated: 2020/07/13 12:13:47 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** Write magic header from COREWAR_EXEC_MAGIC const
*/

void	write_magic(int fd)
{
	int magic;

	magic = COREWAR_EXEC_MAGIC;
	magic = swap_int32(magic);
	write(fd, &magic, 4);
}

/*
** Write 0 (4 bytes)
*/

void	write_null(int fd)
{
	int x;

	x = 0;
	write(fd, &x, 4);
}

/*
** Write champions executable code size in 4 bytes
*/

void	write_exec_size(t_asm *core, int fd)
{
	int size;

	size = core->byte_size;
	size = swap_int32(size);
	write(fd, &size, 4);
}

/*
** Write champions name and fill the remaining PROG_NAME_LENGTH with 0's
*/

void	write_champ_name(t_asm *core, int fd)
{
	int		cnt;
	int		zero;
	char	*str;

	cnt = 0;
	zero = 0;
	str = core->champ_name;
	while (str[cnt] != '\0' && cnt < PROG_NAME_LENGTH)
	{
		write(fd, &str[cnt], 1);
		cnt += 1;
	}
	while (cnt < PROG_NAME_LENGTH)
	{
		write(fd, &zero, 1);
		cnt += 1;
	}
}

/*
** Write champions comment and fill the remaining COMMENT_LENGTH with 0's
*/

void	write_champ_comment(t_asm *core, int fd)
{
	int		cnt;
	int		zero;
	char	*str;

	cnt = 0;
	zero = 0;
	str = core->champ_comment;
	while (str[cnt] != '\0' && cnt < COMMENT_LENGTH)
	{
		write(fd, &str[cnt], 1);
		cnt += 1;
	}
	while (cnt < COMMENT_LENGTH)
	{
		write(fd, &zero, 1);
		cnt += 1;
	}
}
