/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op01_live.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolopov <asolopov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 15:02:59 by jnovotny          #+#    #+#             */
/*   Updated: 2020/07/21 15:01:47 by asolopov         ###   ########.fr       */
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
			ft_printf("A process shows that player %d (%s) is alive\n",\
				core->champ[i]->id, core->champ[i]->header->prog_name);
			break;
		}
		i++;
	}
}

void	op_live(t_vm *core, t_car *car)
{
	uint8_t	*code;
	int		val;
	int		tdir;

	if (LOG)
		vm_log("Carriage[%zu] - operation \"%s\"\n", car->id, g_oplist[car->op_index].opname);
	fill_args("live", car->args);
	code = core->arena + car->pc;
	tdir = car->args->t_dir_size;
	val = decode(code + OP_BYTE, tdir);
	if (LOG)
		vm_log("Performed live with argument: %d\n", val);
	last_to_live(core, (uint8_t)val);
	get_jump(car, car->args);
}
