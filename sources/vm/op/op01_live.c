/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op01_live.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 15:02:59 by jnovotny          #+#    #+#             */
/*   Updated: 2020/07/20 13:32:40 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "oplist_cw.h"

static void		last_to_live(t_vm *core, uint8_t live_arg)
{
	int	i;

	i = 0;
	while (i < core->n_players)
	{
		if (core->champ[i]->id == live_arg)
		{
			core->last_to_live = core->champ[i];
			ft_printf("A process shows that player %d (%s) is alive",\
				core->champ[i]->id, core->champ[i]->header->prog_name);
			break;
		}
		i++;
	}
}

void	op_live(t_vm *core, t_car *car)
{
	if (LOG)
		vm_log("Carriage[%zu] - operation \"%s\"\n", car->id, g_oplist[car->op_index].opname);
	// winner test
	last_to_live(core, 1);
}
