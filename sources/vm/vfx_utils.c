/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vfx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 16:55:22 by jnovotny          #+#    #+#             */
/*   Updated: 2020/07/28 18:01:47 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

char	*create_progress_bar(size_t max_val, size_t cur_val,\
		size_t len, int *color)
{
	double	rat;
	double	l;
	char	*str;

	rat = (double)cur_val / (double)max_val;
	l = rat * len;
	str = ft_strnew((size_t)l);
	ft_strset(str, 35, (size_t)l);
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

void	reset_window(WINDOW *win, int playback)
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
		VFX_FREQ = VFX_FREQ > VFX_SPEED_DELTA ?\
			VFX_FREQ - VFX_SPEED_DELTA : VFX_SPEED_DELTA;
	else if (core->vfx->key == KEY_LEFT)
		VFX_FREQ += VFX_SPEED_DELTA;
	else if (core->vfx->key == KEY_UP)
		vfx_cycle(core);
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
		mvwprintw(VFX_INFO, *y, *x, "Player %3d: %-*s",\
			core->champ[i]->id, len, core->champ[i]->header->prog_name);
		*y += 1;
		buf = create_progress_bar(core->car_cnt, core->champ[i]->car_cnt,\
			core->vfx->info->width - 2 - *x, NULL);
		mvwprintw(VFX_INFO, *y, *x, buf);
		free(buf);
		wattroff(VFX_INFO, COLOR_PAIR(i + 1));
		*y += 2;
		i++;
	}
}
