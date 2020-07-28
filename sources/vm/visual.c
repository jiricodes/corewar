/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 12:26:16 by jnovotny          #+#    #+#             */
/*   Updated: 2020/07/28 08:50:07 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "vfx_tools.h"

int		check_carriage(t_car *head, ssize_t pos)
{
	while (head)
	{
		if (head->pc == pos)
			return (1);
		head = head->next;
	}
	return (0);
}

static void reset_window(WINDOW *win, int playback)
{
	werase(win);
	if (playback)
		wattron(win, COLOR_PAIR(8));
	else
		wattron(win, COLOR_PAIR(1));
	wattron(win, A_STANDOUT);
	wborder(win, '*', '*', '*', '*', '*', '*', '*', '*');
	wattroff(win, A_STANDOUT);
	wattroff(win, COLOR_PAIR(8));
	wattroff(win, COLOR_PAIR(1));
}

void	draw_arena(t_vm *core, size_t limit)
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

char	*create_progress_bar(size_t max_val, size_t cur_val, size_t len, int *color)
{
	double	rat;
	double	l;
	char	*str;
	
	rat = (double)cur_val / (double)max_val;
	l = rat * len;
	str = ft_strnew((size_t)l);
	ft_strset(str, 35, (size_t)l);
	// *color = (1 - rat) * 3 + 1;
	if (color)
	{
		if (rat <= 0.45)
			*color = 3;
		else if (rat > 0.45 && rat <= 0.65)
			*color = 4;
		else if (rat > 0.65 && rat <= 0.85)
			*color = 10;
		else
			*color = 1;
	}
	return (str);
}

void	draw_legend(t_vm *core)
{
	int x;
	int y;

	reset_window(VFX_LEG, VFX_PLAY);
	x = core->vfx->legend->width - 13;
	y = core->vfx->legend->height / 2;
	// vm_log(1, "LEG FREQ x = %d, y = %d\n", x, y);
	mvwprintw(VFX_LEG, y, x, "FREQ %6zu", core->vfx->freq);
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

void	players_info(t_vm *core, int *x, int *y)
{
	int		i;
	char	*buf;
	size_t	len;

	i = 0;
	while (i < core->n_players)
	{
		wattron(VFX_INFO, COLOR_PAIR(i + 1));
		len = core->vfx->info->width - 15 - *x;
		mvwprintw(VFX_INFO, *y, *x, "Player %3d: %-*s", core->champ[i]->id, len, core->champ[i]->header->prog_name);
		*y += 1;
		buf = create_progress_bar(core->car_cnt, core->champ[i]->car_cnt, core->vfx->info->width - 2 - *x, NULL);
		mvwprintw(VFX_INFO, *y, *x, buf);
		free(buf);
		wattroff(VFX_INFO, COLOR_PAIR(i + 1));
		*y += 2;
		i++;
	}
}

void	draw_info(t_vm *core)
{
	char	*buf;
	int		x;
	int		y;
	int		clr;

	reset_window(VFX_INFO, VFX_PLAY);
	x = core->vfx->info->width / 2 - 7;
	y = 1;
	// vm_log(1, "info x = %d, y = %d\n", x, y);
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
	mvwprintw(VFX_INFO, y, x, "Cycle:\t%6zu", core->cycle);
	y++;
	mvwprintw(VFX_INFO, y, x, "CTD:\t\t%6zd", core->cycles_to_die);
	y++;
	mvwprintw(VFX_INFO, y, x, "Live Check:");
	y++;
	clr = 1;
	buf = create_progress_bar(core->cycles_to_die, core->cycles_to_die - core->check_cd, core->vfx->info->width - 4, &clr);
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

void	draw_cycle(t_vm *core)
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

void	init_vfx_arena(t_vm *core)
{
	core->vfx = init_visual_settings();
	vfx_colors();
}

void	vfx_key(t_vm *core)
{
	if (core->vfx->key == ' ')
	{
		core->vfx->play = core->vfx->play ? 0 : 1;
		draw_cycle(core);
	}
	else if (core->vfx->key == 27)
	{
		endwin();
		exit(0);
	}
	else if (core->vfx->key == KEY_RIGHT)
		core->vfx->freq = core->vfx->freq > VFX_SPEED_DELTA ? core->vfx->freq - VFX_SPEED_DELTA : VFX_SPEED_DELTA;
	else if (core->vfx->key == KEY_LEFT)
		core->vfx->freq += VFX_SPEED_DELTA;
}

