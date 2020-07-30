/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vfx_engine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 17:08:32 by jnovotny          #+#    #+#             */
/*   Updated: 2020/07/30 17:50:35 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "oplist_cw.h"

void			vfx_announce_winner(t_vm *core)
{
	core->vfx->play = 0;
	wattron(core->vfx->info->win, A_STANDOUT);
	wattron(core->vfx->info->win, COLOR_PAIR(3));
	if (core->last_to_live)
		mvwprintw(core->vfx->info->win, core->vfx->info->height - 10, 2,\
			"Player (%d) %s won", core->last_to_live->id,\
				core->last_to_live->header->prog_name);
	else
		mvwprintw(core->vfx->info->win, core->vfx->info->height - 10, 2,\
			"Everyone is dead, total clusterfuck");
	wrefresh(core->vfx->info->win);
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
	log_vm_status(core, core->flags->log);
}

void			vfx_cycle(t_vm *core)
{
	core->check_cd--;
	do_cycle(core);
	if (core->check_cd <= 0)
		check_lives(core);
	draw_cycle(core);
	core->cycle++;
}

void			vfx_engine(t_vm *core)
{
	size_t	loop;

	loop = 0;
	init_vfx_arena(core);
	draw_cycle(core);
	while (core->car_list && core->cycles_to_die >= 0)
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
}
