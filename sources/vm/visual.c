/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 12:26:16 by jnovotny          #+#    #+#             */
/*   Updated: 2020/07/26 19:18:01 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void get_term_size(int *height, int *width) {
    struct winsize ws = {0, 0, 0, 0};
    if (ioctl(0, TIOCGWINSZ, &ws) < 0)
        vm_error("Failed to retrieve terminal size", LOG);
    *height = ws.ws_row;
    *width = ws.ws_col;
}

static t_win	*init_window(int height, int width, int x, int y)
{
	t_win	*window;

	window = (t_win *)ft_memalloc(sizeof(t_win));
	if (!window)
		vm_error("Malloc at init_window", LOG);
	window->win = newwin(height, width, y, x);
	window->height = height;
	window->width = width;
	window->x = x;
	window->y = y;
	return (window);
}

t_vs	*init_visual_settings(void)
{
	t_vs	*settings;
	int		height;
	int		width;

	settings = (t_vs *)ft_memalloc(sizeof(t_vs));
	if (!settings)
		vm_error("Malloc at init_visual_settings", LOG);
	get_term_size(&height, &width);
	settings->time.tv_sec = VFX_SLEEP_S;
	settings->time.tv_nsec = VFX_SLEEP_N;
	settings->freq = VFX_INIT_SPEED;
	initscr();
	keypad(stdscr, true);
	nodelay(stdscr, true);
	curs_set(0);
	cbreak();
	noecho();
	settings->arena = init_window(MEM_SIZE / VFX_WIDTH + 2, VFX_WIDTH * 2 + 2, 0, 0);
	if (width > settings->arena->width)
		settings->info = init_window(settings->arena->height, width - settings->arena->width + 1, settings->arena->x + settings->arena->width - 1, settings->arena->y);
	else
		settings->info = init_window(settings->arena->height, VFX_INFO_STD, settings->arena->x + settings->arena->width - 1, settings->arena->y);
	if (height > settings->arena->height)
		settings->legend = init_window(height - settings->arena->height + 1, width, 0, settings->arena->height - 1);
	else
		settings->legend = init_window(VFX_LEGEND_STD, width, 0, settings->arena->height - 1);
	refresh();
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

void	draw_arena(t_vm *core)
{
	size_t	i;
	int		hgl;
	int		x;
	int		y;

	reset_window(VFX_ARENA, VFX_PLAY);
	i = 0;
	while (i < MEM_SIZE)
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

void	draw_legend(t_vm *core)
{
	int x;
	int y;

	reset_window(VFX_LEG, VFX_PLAY);
	x = core->vfx->legend->width - 13;
	y = core->vfx->legend->height / 2;
	vm_log(1, "LEG FREQ x = %d, y = %d\n", x, y);
	mvwprintw(VFX_LEG, y, x, "FREQ %6zu", core->vfx->freq);
	wrefresh(VFX_LEG);
}

void	draw_info(t_vm *core)
{
	char	*buf;
	int		x;
	int		y;

	reset_window(VFX_INFO, VFX_PLAY);
	x = core->vfx->info->width / 2 - 7;
	y = 1;
	vm_log(1, "info x = %d, y = %d\n", x, y);
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
	wrefresh(VFX_INFO);
}

void	draw_cycle(t_vm *core)
{
	draw_arena(core);
	draw_legend(core);
	draw_info(core);
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

