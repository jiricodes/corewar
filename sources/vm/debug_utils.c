/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 11:48:04 by jnovotny          #+#    #+#             */
/*   Updated: 2020/07/24 19:51:27 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static size_t	*sort_ids(size_t *ids, size_t lenght)
{
	size_t	tmp;
	size_t	i;
	size_t	k;
	size_t *result;

	if (lenght == 1)
		return (ids);
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

static void	intro_champ(t_vm *core, size_t id)
{
	int i;

	i = 0;
	while (core->champ[i]->id != id)
		i++;
	ft_printf("* Player %zu, weighing %u bytes, \"%s\" (\"%s\")\n", core->champ[i]->id, core->champ[i]->header->prog_size, core->champ[i]->header->prog_name, core->champ[i]->header->comment);
}

void	introduce_champs(t_vm *core)
{
	size_t	*ids;
	int	i;

	ids = (size_t *)ft_memalloc(sizeof(size_t) * core->n_players);
	if (!ids)
		vm_error("Malloc at introduce_champs", core->flags->log);
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
}
