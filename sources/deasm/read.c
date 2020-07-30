/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolopov <asolopov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 16:15:15 by asolopov          #+#    #+#             */
/*   Updated: 2020/07/30 10:19:50 by asolopov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "deasm.h"

/*
** reads 4 bytes and decodes to get magic header
*/

static void		read_magic(int source_fd)
{
	int		ret;
	uint8_t	buffer[4];
	int32_t	magic;

	ret = read(source_fd, buffer, 4);
	if (ret < 4)
		ft_error_exit("Magic error", 0, 0);
	magic = decode(buffer, 4);
	if (magic != COREWAR_EXEC_MAGIC)
		ft_error_exit("Magic is incorrect", 0, 0);
}

/*
** reads and decodes n bytes
*/

static int32_t	read_bytes(int source_fd, int size)
{
	int		ret;
	uint8_t	buffer[size];

	ret = read(source_fd, buffer, size);
	if (ret < size)
		ft_error_exit("File read error", 0, 0);
	return (decode(buffer, size));
}

/*
** reads n bytes and returns str
*/

static char		*read_str(int source_fd, int size)
{
	char	*buffer;
	int		ret;

	buffer = ft_strnew(size + 1);
	if (!buffer)
		ft_error_exit("Couldn't create buffer", 0, 0);
	ret = read(source_fd, buffer, size);
	if (ret != size)
		ft_error_exit("Couldn't read string", 0, 0);
	return (buffer);
}

/*
** reads n bytes of exec code and returns int array
*/

static int8_t	*read_exec_code(int source_fd, int size)
{
	int8_t	*code;
	int		ret;

	code = (int8_t *)malloc(size);
	if (!code)
		ft_error_exit("Couldn't malloc code array", 0, 0);
	if (size == 0)
	{
		ret = read(source_fd, code, size + 1);
		if (ret)
			ft_error_exit("Expected zero bytes of exec code", 0, 0);
		else
			ret = 0;
	}
	else
		ret = read(source_fd, code, size);
	if (ret != size)
		ft_error_exit("Incorrect champ size or exec code", 0, 0);
	return (code);
}

/*
** func to read contents of .cor file
*/

void			read_file(t_deasm *core, int source_fd)
{
	read_magic(source_fd);
	core->champ_name = read_str(source_fd, PROG_NAME_LENGTH);
	if (read_bytes(source_fd, 4) != 0)
		ft_error_exit("null space error", 0, 0);
	core->exec_code_size = read_bytes(source_fd, 4);
	core->champ_comment = read_str(source_fd, COMMENT_LENGTH);
	if (read_bytes(source_fd, 4) != 0)
		ft_error_exit("null space error", 0, 0);
	core->raw_code = read_exec_code(source_fd, core->exec_code_size);
}
