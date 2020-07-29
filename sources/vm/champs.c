/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 10:48:05 by jnovotny          #+#    #+#             */
/*   Updated: 2020/07/29 17:04:48 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_champ		*init_champ(char *filename, uint8_t id)
{
	t_champ		*champ;
	char		*buf;

	if (!ft_strendwith(filename, ".cor"))
	{
		ft_dprintf(2, "Incorrect file type: %s\n", filename);
		vm_error("File Type", LOG);
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
			ft_dprintf(2, "Champ [%s] source.\n", champs[i]->header->prog_name);
			vm_error("Close FD", LOG);
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
		ft_dprintf(2, "Player %zu cannot read file or too short\n", champ->id);
		vm_error("Magic Invalid Size", LOG);
	}
	champ->header->magic = decode(buffer, 4);
	if (champ->header->magic != (unsigned int)COREWAR_EXEC_MAGIC)
	{
		ft_dprintf(2, "Player %u\n", champ->id);
		vm_error("Magic Invalid", LOG);
	}
	return ;
}

int32_t		decode_bytes(t_champ *champ, size_t size)
{
	ssize_t	ret;
	uint8_t buffer[size];
	char	*buf;

	ret = read(champ->fd, buffer, size);
	if (ret < size)
	{
		ft_dprintf(2, "Player %zu cannot read file or too short\n", champ->id);
		vm_error("File too short", LOG);
	}
	return (decode(buffer, size));
}

void		load_champ(t_champ *champ)
{
	load_header(champ);
	load_code(champ);
}
