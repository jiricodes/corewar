/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 15:30:23 by jnovotny          #+#    #+#             */
/*   Updated: 2020/07/29 17:15:22 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

char		*load_string(t_champ *champ, size_t size)
{
	char	*buffer;
	ssize_t	ret;

	buffer = ft_strnew(size + 1);
	if (!buffer)
		vm_error("Malloc at load_string", LOG);
	ret = read(champ->fd, buffer, size);
	if (ret != (ssize_t)size)
	{
		ft_dprintf(2, "Player %u cannot read file or too short\n", champ->id);
		vm_error("Load String", LOG);
	}
	buffer[ret] = '\0';
	return (buffer);
}

static void	check_null_bytes(t_champ *champ, int index)
{
	if (decode_bytes(champ, 4) != 0)
	{
		ft_dprintf(2, "Player %u - %d. NULL error\n", champ->id, index);
		vm_error("NULL Check", LOG);
	}
}

void		load_header(t_champ *champ)
{
	char *tmp;

	magic_check(champ);
	tmp = load_string(champ, PROG_NAME_LENGTH);
	ft_strcpy(champ->header->prog_name, tmp);
	free(tmp);
	check_null_bytes(champ, 1);
	champ->header->prog_size = decode_bytes(champ, 4);
	if (champ->header->prog_size > CHAMP_MAX_SIZE ||\
		champ->header->prog_size < 0)
	{
		ft_dprintf(2, "Player %zu - champ size must be 0 < size <= %zu\n",\
			champ->id, CHAMP_MAX_SIZE);
		vm_error("Champion Size", LOG);
	}
	tmp = load_string(champ, COMMENT_LENGTH);
	ft_strcpy(champ->header->comment, tmp);
	free(tmp);
	check_null_bytes(champ, 2);
}

void		load_code(t_champ *champ)
{
	uint8_t *code;
	ssize_t ret;
	char	*temp;

	temp = NULL;
	code = (uint8_t *)ft_memalloc(champ->header->prog_size);
	if (!code)
		vm_error("Malloc at load_code", LOG);
	ret = read(champ->fd, code, champ->header->prog_size);
	if (ret != champ->header->prog_size || read(champ->fd, temp, 1) > 0)
	{
		ft_dprintf(2, "Player %zu - code lenght != prog_size\n",\
			champ->id, CHAMP_MAX_SIZE);
		vm_error("Champion Code Lenght", LOG);
	}
	champ->raw = code;
}
