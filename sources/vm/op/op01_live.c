/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op01_live.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 15:02:59 by jnovotny          #+#    #+#             */
/*   Updated: 2020/08/07 07:16:40 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "oplist_cw.h"

inline void	log_live(t_vm *core, t_car *car, int val)
{
	char *tmp;

	if (!core->flags->vfx)
		ft_printf("[%zu]\tP %4zu | %s %d\n", core->cycle, car->id, "live", val);
	else
	{
		tmp = ft_strnew(LOG_BUF);
		ft_sprintf(tmp, " [%zu]\tP %4zu | %s %d\n", core->cycle,\
			car->id, "live", val);
		vfx_write_log(core, tmp, car->pc);
		free(tmp);
	}
}

static void	last_to_live(t_vm *core, int live_arg)
{
	int	i;

	i = 0;
	if (live_arg >= 0)
		return ;
	while (i < core->n_players)
	{
		if (core->champ[i]->id == (size_t)(-1 * live_arg))
		{
			core->last_to_live = core->champ[i];
			if (!core->flags->silent)
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
		if (core->flags->log & LOG_OPS)
			log_live(core, car, val);
		last_to_live(core, val);
		car->last_live = core->cycle;
		core->live_cnt++;
	}
	get_step(car, car->args);
}
