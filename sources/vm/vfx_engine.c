/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vfx_engine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 17:08:32 by jnovotny          #+#    #+#             */
/*   Updated: 2020/07/28 06:30:52 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "oplist_cw.h"

void			vfx_announce_winner(t_vm *core)
{
	VFX_PLAY = 0;
	wattron(VFX_INFO, A_STANDOUT);
	wattron(VFX_INFO, COLOR_PAIR(3));
	if (core->last_to_live)
		mvwprintw(VFX_INFO, core->vfx->info->height - 10, 2,\
			"Player (%d) %s won", core->last_to_live->id, WINNER);
	else
		mvwprintw(VFX_INFO, core->vfx->info->height - 10, 2,\
			"Everyone is dead, total clusterfuck");
	wrefresh(VFX_INFO);
	while (1)
	{
		if (getch() != ERR)
			break ;
	}
}

static void		do_vfx_dump(t_vm *core)
{
	VFX_PLAY = 0;
	draw_cycle(core);
	log_vm_status(core, F_LOG);
}

void			vfx_engine(t_vm *core)
{
	size_t	loop;

	loop = 0;
	init_vfx_arena(core);
	draw_cycle(core);
	while (core->car_list && CTD >= 0)
	{
		if ((core->vfx->key = getch()) != ERR)
			vfx_key(core);
		if (core->cycle == core->flags->dump_cycle)
			do_vfx_dump(core);
		if (VFX_PLAY && loop % core->vfx->freq == 0)
		{
			loop = 0;
			core->check_cd--;
			do_cycle(core);
			if (core->check_cd <= 0)
				check_lives(core);
			draw_cycle(core);
			core->cycle++;
		}
		loop++;
	}
	vfx_announce_winner(core);
	endwin();
}
