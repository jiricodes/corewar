/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 12:26:16 by jnovotny          #+#    #+#             */
/*   Updated: 2020/07/24 20:17:03 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_vs	*init_visual_settings(char *title)
{
	t_vs	*settings;

	settings = (t_vs *)ft_memalloc(sizeof(t_vs));
	if (!settings)
		vm_error("Malloc at init_visual_settings", LOG);
	settings->height = 66;
	settings->width = 64 * 2 + 2;
	settings->time.tv_sec = VFX_SLEEP_S;
	settings->time.tv_nsec = VFX_SLEEP_N;
	settings->freq = VFX_INIT_SPEED;
	initscr();
	keypad(stdscr, true);
	nodelay(stdscr, true);
	curs_set(0);
	cbreak();
	noecho();
	mvprintw(0,20, title);
	settings->win = newwin(settings->height, settings->width, 1, 0);
	refresh();
	box(settings->win, 0, 0);
	return (settings);
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
void	draw_arena(t_vm *core)
{
	int	y;
	int	x;
	ssize_t	i;
	int	hgl;

	werase(core->vfx->win);
	y = 1;
	x = 1;
	i = 0;
	while (i < MEM_SIZE)
	{
		if ((hgl = check_carriage(core->car_list, i)))
			wattron(core->vfx->win, A_STANDOUT);
		wattron(core->vfx->win, COLOR_PAIR((int)(core->byte_owner[i])));
		mvwprintw(core->vfx->win, y, x, "%02x", core->arena[i]);
		wattroff(core->vfx->win, COLOR_PAIR((int)(core->byte_owner[i])));
		if (hgl)
			wattroff(core->vfx->win, A_STANDOUT);
		i++;
		x += 2;
		if (x >= core->vfx->width - 1)
		{
			x = 1;
			y++;
		}
	}
	wrefresh(core->vfx->win);
}

void	init_vfx_arena(t_vm *core)
{
	core->vfx = init_visual_settings("COREWAR");
	vfx_colors();
}

void	vfx_key(t_vs *vfx)
{
	if (vfx->key == ' ')
		vfx->play = vfx->play ? 0 : 1;
	else if (vfx->key == 27)
	{
		endwin();
		exit(0);
	}
	else if (vfx->key == KEY_RIGHT)
		vfx->freq = vfx->freq > VFX_SPEED_DELTA ? vfx->freq - VFX_SPEED_DELTA : VFX_SPEED_DELTA;
	else if (vfx->key == KEY_LEFT)
		vfx->freq += VFX_SPEED_DELTA;
}