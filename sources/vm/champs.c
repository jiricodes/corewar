/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 10:48:05 by jnovotny          #+#    #+#             */
/*   Updated: 2020/06/10 12:32:00 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_champ		*init_champ(char	*filename)
{
	t_champ		*champ;

	if (!ft_strendwith(filename, ".cor"))
	{
		ft_printf("Incorrect file type: %s\n", filename);
		ft_error_exit("Must be .cor type. Terminating", NULL, NULL);
	}
	champ = (t_champ*)ft_memalloc(sizeof(t_champ));
	if (!champ)
		ft_error_exit("Malloc at init_champ", NULL, NULL);
	if ((champ->fd = open(filename, O_RDONLY)) < 0)
		ft_error_exit(filename, NULL, NULL);
	champ->header = (header_t *)ft_memalloc(sizeof(header_t));
	if (!(champ->header))
		ft_error_exit("Malloc header in init_champ", NULL, NULL);
	return (champ);
}

void		magic_check(t_champ *champ)
{
	size_t	ret;
	uint8_t buffer[4];

	ret = read(champ->fd, buffer, 4);
	if (ret < 4)
		ft_error_exit("Magic error - file cannot be read or is too short", NULL, NULL);
	champ->header->magic = decode(buffer, 4);
	if (champ->header->magic != COREWAR_EXEC_MAGIC)
		ft_error_exit("Magic error - Magic differs from DEFINED", NULL, NULL);
	return;
}

uint8_t		nullbytes_check(t_champ *champ, size_t size)
{
	size_t	ret;
	uint8_t buffer[size];

	ret = read(champ->fd, buffer, size);
	if (ret < size)
		ft_error_exit("Null byte check - file read error or too short", NULL, NULL);
	return (decode(buffer, size) == 0 ? 1 : 0);
}

char		*load_string(t_champ *champ, size_t size)
{
	char	*buffer;
	size_t	ret;

	buffer = ft_strnew(size + 1);
	if (!buffer)
		ft_error_exit("Malloc at load_string", NULL, NULL);
	ret = read(champ->fd, buffer, size);
	if (ret != size)
		ft_error_exit("load_string error, cannot read given size", NULL, NULL);
	buffer[ret] = '\0';
	ft_printf("Read: %s\n", buffer);
	return (buffer);
}

void		load_header(t_champ *champ)
{
	char *tmp;

	magic_check(champ);
	tmp = load_string(champ, PROG_NAME_LENGTH);
	ft_strcpy(champ->header->prog_name, tmp);
	free(tmp);
	if (nullbytes_check(champ, 4))
		ft_error_exit("First NULL spacing error", NULL, NULL);
	// if (nullbytes_check(champ, 4))
	// 	ft_error_exit("Second NULL spacing error", NULL, NULL);
}

void		load_champ(t_champ *champ)
{
	load_header(champ);
	ft_printf("Header loaded\n");
	print_champ_header(champ);
}