/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vfx_engine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 17:08:32 by jnovotny          #+#    #+#             */
/*   Updated: 2020/08/11 14:21:06 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "oplist_cw.h"

void			vfx_announce_winner(t_vm *core)
{
	core->vfx->play = 0;
	wattron(core->vfx->log->win, A_STANDOUT | COLOR_PAIR(3));
	if (core->last_to_live)
		wprintw(core->vfx->log->win, "  Player (%d) %s won!!!\n", \
			core->last_to_live->id, core->last_to_live->header->prog_name);
	wattroff(core->vfx->log->win, A_STANDOUT | COLOR_PAIR(3));
	wprintw(core->vfx->log->win, "\n  PRESS ANY KEY TO EXIT\n\n");
	draw_log(core);
	while (1)
	{
		if (getch() != ERR)
			break ;
	}
}

static void		do_vfx_dump(t_vm *core)
{
	core->vfx->play = 0;
	draw_cycle(core);
}

void			vfx_cycle(t_vm *core)
{
	core->cycle++;
	core->check_cd--;
	do_cycle(core);
	if (core->check_cd <= 0)
		check_lives(core);
	draw_cycle(core);
}

void			free_vfx(t_vm *core)
{
	free(core->vfx->arena);
	free(core->vfx->info);
	free(core->vfx->legend);
	free(core->vfx->log);
	free(core->vfx->car_map);
	free(core->vfx);
}

void			vfx_engine(t_vm *core)
{
	size_t	loop;

	loop = 0;
	init_vfx_arena(core);
	draw_cycle(core);
	while (core->car_list)
	{
		if ((core->vfx->key = getch()) != ERR)
			vfx_key(core);
		if (core->vfx->play && loop % core->vfx->freq == 0)
		{
			loop = 0;
			vfx_cycle(core);
		}
		if (core->cycle == core->flags->dump_cycle)
			do_vfx_dump(core);
		loop++;
	}
	vfx_announce_winner(core);
	endwin();
	free_vfx(core);
}
