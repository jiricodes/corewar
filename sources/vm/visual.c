/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 12:26:16 by jnovotny          #+#    #+#             */
/*   Updated: 2020/07/28 17:02:00 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "vfx_tools.h"

void		draw_arena(t_vm *core, size_t limit)
{
	size_t	i;
	int		hgl;
	int		x;
	int		y;

	reset_window(VFX_ARENA, VFX_PLAY);
	i = 0;
	while (i < limit)
	{
		if ((hgl = check_carriage(core->car_list, i)))
			wattron(VFX_ARENA, A_STANDOUT);
		wattron(VFX_ARENA, COLOR_PAIR((int)(core->byte_owner[i])));
		x = ((i % (VFX_WIDTH)) * 2) + 1;
		y = (i / (core->vfx->arena->height - 2)) + 1;
		mvwprintw(VFX_ARENA, y, x, "%02x", core->arena[i]);
		wattroff(VFX_ARENA, COLOR_PAIR((int)(core->byte_owner[i])));
		if (hgl)
			wattroff(VFX_ARENA, A_STANDOUT);
		i++;
	}
	wrefresh(VFX_ARENA);
}

void		draw_legend(t_vm *core)
{
	int x;
	int y;

	reset_window(VFX_LEG, VFX_PLAY);
	x = core->vfx->legend->width - 13;
	y = core->vfx->legend->height / 2;
	mvwprintw(VFX_LEG, y, x, "FREQ %6zu", VFX_FREQ);
	x = 4;
	mvwprintw(VFX_LEG, y, x, L_SLOW);
	x += ft_strlen(L_SLOW) + 4;
	mvwprintw(VFX_LEG, y, x, L_FAST);
	x += ft_strlen(L_FAST) + 4;
	mvwprintw(VFX_LEG, y, x, L_PLAY);
	x += ft_strlen(L_PLAY) + 4;
	mvwprintw(VFX_LEG, y, x, L_EXIT);
	wrefresh(VFX_LEG);
}

static void	draw_info_pt2(t_vm *core, int x, int y)
{
	char	*buf;
	int		clr;

	mvwprintw(VFX_INFO, y, x, "Cycle:\t%6zu", core->cycle);
	y++;
	mvwprintw(VFX_INFO, y, x, "CTD:\t\t%6zd", core->cycles_to_die);
	y++;
	mvwprintw(VFX_INFO, y, x, "Live Check:");
	y++;
	clr = 1;
	buf = create_progress_bar(core->cycles_to_die,\
		core->cycles_to_die - core->check_cd, core->vfx->info->width - 4, &clr);
	wattron(VFX_INFO, COLOR_PAIR(clr));
	mvwprintw(VFX_INFO, y, x, buf);
	wattroff(VFX_INFO, COLOR_PAIR(clr));
	free(buf);
	y += 2;
	mvwprintw(VFX_INFO, y, x, "PC count:\t%6zu", core->car_cnt);
	y += 2;
	players_info(core, &x, &y);
	wrefresh(VFX_INFO);
}

void		draw_info(t_vm *core)
{
	int		x;
	int		y;

	reset_window(VFX_INFO, VFX_PLAY);
	x = core->vfx->info->width / 2 - 7;
	y = 1;
	if (core->vfx->play)
	{
		wattron(VFX_INFO, COLOR_PAIR(3));
		mvwprintw(VFX_INFO, y, x, "*** RUNNING ***");
		wattroff(VFX_INFO, COLOR_PAIR(3));
	}
	else
	{
		wattron(VFX_INFO, COLOR_PAIR(1));
		mvwprintw(VFX_INFO, y, x, "*** PAUSED ***");
		wattroff(VFX_INFO, COLOR_PAIR(1));
	}
	y += 2;
	x = 2;
	draw_info_pt2(core, x, y);
}

void		draw_cycle(t_vm *core)
{
	size_t	loop;
	size_t	limit;

	draw_legend(core);
	draw_info(core);
	if (!core->cycle && !core->vfx->play)
	{
		limit = 1;
		loop = 0;
		while (limit <= MEM_SIZE)
		{
			if (loop >= VFX_ANIM_SPEED)
			{
				loop = 0;
				draw_arena(core, limit);
				limit = limit + 1;
			}
			loop++;
		}
	}
	else
		draw_arena(core, MEM_SIZE);
}
