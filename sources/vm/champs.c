/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 10:48:05 by jnovotny          #+#    #+#             */
/*   Updated: 2020/07/24 19:43:11 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_champ		*init_champ(char *filename, uint8_t id)
{
	t_champ		*champ;
	char		*buf;

	if (!ft_strendwith(filename, ".cor"))
	{
		ft_sprintf(buf, "Incorrect file type: %s\n", filename);
		vm_error(buf, LOG);
	}
	champ = (t_champ*)ft_memalloc(sizeof(t_champ));
	if (!champ)
		vm_error("Malloc at init_champ", LOG);
	if ((champ->fd = open(filename, O_RDONLY)) < 0)
		vm_error(filename, LOG);
	champ->header = (header_t *)ft_memalloc(sizeof(header_t));
	if (!(champ->header))
		vm_error("Malloc header in init_champ", LOG);
	champ->id = id;
	return (champ);
}

void		delete_champs(t_champ **champs, int n)
{
	int		i;
	int		stat;
	char	*buf;

	i = 0;
	while (i < n)
	{
		stat = close(champs[i]->fd);
		if (stat == -1)
		{
			ft_sprintf(buf, "Champ [%s] source.", champs[i]->header->prog_name);
			vm_error(buf, LOG);
		}
		free(champs[i]->raw);
		free(champs[i]->header);
		free(champs[i]);
		i++;
	}
	free(champs);
}

void		magic_check(t_champ *champ)
{
	ssize_t	ret;
	uint8_t buffer[4];
	char	*buf;

	ret = read(champ->fd, buffer, 4);
	if (ret < 4)
	{
		ft_sprintf(buf, "Player %zu cannot read file or too short", champ->id);
		vm_error(buf, LOG);
	}
	champ->header->magic = decode(buffer, 4);
	if (champ->header->magic != COREWAR_EXEC_MAGIC)
	{
		ft_sprintf(buf, "Player %zu - Magic Error", champ->id);
		vm_error(buf, LOG);
	}
	return;
}

int32_t		decode_bytes(t_champ *champ, size_t size)
{
	ssize_t	ret;
	uint8_t buffer[size];
	char	*buf;

	ret = read(champ->fd, buffer, size);
	if (ret < size)
	{
		ft_sprintf(buf, "Player %zu cannot read file or too short", champ->id);
		vm_error(buf, LOG);
	}
	return (decode(buffer, size));
}

char		*load_string(t_champ *champ, size_t size)
{
	char	*buffer;
	char	*buf;
	ssize_t	ret;

	buffer = ft_strnew(size + 1);
	if (!buffer)
		vm_error("Malloc at load_string", LOG);
	ret = read(champ->fd, buffer, size);
	if (ret != size)
	{
		ft_sprintf(buf, "Player %zu cannot read file or too short", champ->id);
		vm_error(buf, LOG);
	}
	buffer[ret] = '\0';
	ft_printf("Read: %s\n", buffer);
	return (buffer);
}

void		load_header(t_champ *champ)
{
	char *tmp;
	char *buf;

	magic_check(champ);
	tmp = load_string(champ, PROG_NAME_LENGTH);
	ft_strcpy(champ->header->prog_name, tmp);
	free(tmp);
	if (decode_bytes(champ, 4) != 0)
	{
		ft_sprintf(buf, "Player %zu First NULL error", champ->id);
		vm_error(buf, LOG);
	}
	champ->header->prog_size = decode_bytes(champ, 4);
	if (champ->header->prog_size > CHAMP_MAX_SIZE || champ->header->prog_size < 0)
	{
		ft_sprintf(buf, "Player %zu - champ size must be 0 < size <= %zu", champ->id, CHAMP_MAX_SIZE);
		vm_error(buf, LOG);
	}
	tmp = load_string(champ, COMMENT_LENGTH);
	ft_strcpy(champ->header->comment, tmp);
	free(tmp);
	if (decode_bytes(champ, 4) != 0)
	{
		ft_sprintf(buf, "Player %zu Second NULL error", champ->id);
		vm_error(buf, LOG);
	}
}

void		load_code(t_champ *champ)
{
	uint8_t *code;
	ssize_t ret;
	char	*buf;
	char	*temp;

	code = (uint8_t *)ft_memalloc(champ->header->prog_size);
	if (!code)
		vm_error("Malloc at load_code", LOG);
	ret = read(champ->fd, code, champ->header->prog_size);
	if (ret != champ->header->prog_size || read(champ->fd, temp, 1) > 0)
	{
		ft_sprintf(buf, "Player %zu - code lenght != prog_size", champ->id, CHAMP_MAX_SIZE);
		vm_error(buf, LOG);
	}
	champ->raw = code;
}

void		load_champ(t_champ *champ)
{
	load_header(champ);
	load_code(champ);
}