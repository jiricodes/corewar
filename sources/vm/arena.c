/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 12:28:33 by jnovotny          #+#    #+#             */
/*   Updated: 2020/07/24 20:45:02 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	init_arena(t_vm	*core)
{
	core->arena = (uint8_t *)ft_memalloc(MEM_SIZE);
	if (!(core->arena))
		vm_error("Malloc at init_arena [arena]", LOG);
	core->byte_owner = (uint8_t *)ft_memalloc(MEM_SIZE);
	if (!(core->byte_owner))
		vm_error("Malloc at init_arena [byte_owner]", LOG);
}

static uint8_t	champ_index(t_vm *core, size_t id)
{
	uint8_t i;

	i = 0;
	while (core->champ[i]->id != id)
		i++;
	return (i);
}

void	insert_champ_to_arena(t_vm *core, t_champ *champ, ssize_t position)
{
	size_t	i;
	char	*buf;
	uint8_t chi;

	i = 0;
	chi = champ_index(core, champ->id) + 1;
	while (i < champ->header->prog_size)
	{
		if (core->arena[position + i])
		{
			ft_sprintf(buf, "Inserting Player %zu error. Byte [%zu] overwrite", champ->id, position + 1);
			vm_error(buf, F_LOG);
		}
		core->arena[position + i] = champ->raw[i];
		core->byte_owner[position + i] = chi;
		i++;
		if (position + i == MEM_SIZE)
			position = -1 * i;
	}
}

void	print_arena(uint8_t *arena, int	size)
{
	int	i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (i != 0 && i % size == 0)
			ft_printf("\n");
		if (i % size == 0)
			ft_printf("%#06x :", i);
		else
			ft_printf(" %02x", arena[i]);
		i++;
	}
	ft_printf("\n");
}
