/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op01_live.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 15:02:59 by jnovotny          #+#    #+#             */
/*   Updated: 2020/08/04 18:42:13 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "oplist_cw.h"

static void	last_to_live(t_vm *core, int live_arg)
{
	int	i;

	i = 0;
	while (i < core->n_players)
	{
		if (core->champ[i]->id == (size_t)live_arg)
		{
			core->last_to_live = core->champ[i];
			if (!core->flags->silent && !core->flags->log)
				ft_printf("A process shows that player %d (%s) is alive\n",\
				core->champ[i]->id, core->champ[i]->header->prog_name);
			break ;
		}
		i++;
	}
}

void		op_live(t_vm *core, t_car *car)
{
	ssize_t	index;
	int		val;

	index = car->pc + OP_SIZE;
	if (read_args(core, car->args, index % MEM_SIZE))
	{
		val = car->args->arg[0];
		if (val < 0)
			val *= -1;
		if (core->flags->log & LOG_OPS)
		{
			ft_printf(OP_STR, core->cycle, car->id, "live");
			ft_printf("%d\n", val);
		}
		last_to_live(core, val);
		car->last_live = core->cycle;
		core->live_cnt++;
	}
	get_step(car, car->args);
}
