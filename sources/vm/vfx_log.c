/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vfx_log.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 16:51:47 by jnovotny          #+#    #+#             */
/*   Updated: 2020/08/07 05:40:16 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	vfx_write_log(t_vm *core, char *str)
{
	int y;
	int x;

	getyx(core->vfx->log->win, y, x);
	wmove(core->vfx->log->win, y, x + 1);
	wprintw(core->vfx->log->win, str);
}

void	draw_log(t_vm *core)
{
	if (core->vfx->play)
		wattron(core->vfx->log->win, COLOR_PAIR(8));
	else
		wattron(core->vfx->log->win, COLOR_PAIR(1));
	wattron(core->vfx->log->win, A_STANDOUT);
	wborder(core->vfx->log->win, '*', '*', '*', '*', '*', '*', '*', '*');
	wattroff(core->vfx->log->win, A_STANDOUT);
	wattroff(core->vfx->log->win, COLOR_PAIR(8));
	wattroff(core->vfx->log->win, COLOR_PAIR(1));
	wrefresh(core->vfx->log->win);
}
