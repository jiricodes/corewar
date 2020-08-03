/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 11:48:04 by jnovotny          #+#    #+#             */
/*   Updated: 2020/08/03 14:17:09 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static size_t	*sort_ids(size_t *ids, size_t lenght)
{
	size_t	tmp;
	size_t	i;
	size_t	k;

	i = 1;
	while (i < lenght)
	{
		if (ids[i - 1] > ids[i])
		{
			k = 0;
			while (ids[i] > ids[k])
				k++;
			while (k < i)
			{
				tmp = ids[k];
				ids[k] = ids[i];
				ids[i] = tmp;
				k++;
			}
		}
		i++;
	}
	return (ids);
}

static void		intro_champ(t_vm *core, size_t id)
{
	int		i;
	ssize_t	position;

	i = 0;
	while (core->champ[i]->id != id)
		i++;
	ft_printf("* Player %zu, weighing %u bytes, \"%s\" (\"%s\") !\n",\
		core->champ[i]->id, core->champ[i]->header->prog_size,\
		core->champ[i]->header->prog_name, core->champ[i]->header->comment);
	position = i * MEM_SIZE / core->n_players;
	insert_champ_to_arena(core, core->champ[i], position);
	if (core->flags->log & LOG_DETAILS)
		ft_printf("Champ [%zu] inserted to arena\n",\
			core->champ[i]->id);
	core->car_list = prepend_carriage(core->car_list,\
		create_carriage(core->car_id, position, (uint8_t)core->champ[i]->id));
	core->car_id++;
	core->last_to_live = core->champ[i];
}

void			introduce_champs(t_vm *core)
{
	size_t	*ids;
	int		i;

	ids = (size_t *)ft_memalloc(sizeof(size_t) * core->n_players);
	if (!ids)
		vm_error("Malloc at introduce_champs");
	i = 0;
	while (i < core->n_players)
	{
		ids[i] = core->champ[i]->id;
		i++;
	}
	ids = sort_ids(ids, core->n_players);
	i = 0;
	ft_printf("Introducing contestants...\n");
	while (i < core->n_players)
	{
		intro_champ(core, ids[i]);
		i++;
	}
	free(ids);
}
