/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 12:28:33 by jnovotny          #+#    #+#             */
/*   Updated: 2020/06/12 15:07:27 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	init_arena(t_vm	*core)
{
	core->arena = (uint8_t *)ft_memalloc(MEM_SIZE);
	if (!(core->arena))
		ft_error_exit("Malloc at init_arena", NULL, NULL);
	core->byte_owner = (uint8_t *)ft_memalloc(MEM_SIZE);
	if (!(core->byte_owner))
		ft_error_exit("Malloc at init_arena", NULL, NULL);
}

void	insert_champ_to_arena(t_vm *core, t_champ *champ, ssize_t position)
{
	size_t	i;

	i = 0;
	while (i < champ->header->prog_size)
	{
		core->arena[position + i] = champ->raw[i];
		core->byte_owner[position + i] = champ->id;
		i++;
		if (position + i == MEM_SIZE)
			position = -1 * i;
	}
}