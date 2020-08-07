/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vfx_term.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 08:13:58 by jnovotny          #+#    #+#             */
/*   Updated: 2020/08/07 11:21:11 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "vfx_tools.h"

void		get_term_size(int *height, int *width)
{
	struct winsize	ws;

	ws.ws_col = 0;
	ws.ws_row = 0;
	ws.ws_xpixel = 0;
	ws.ws_ypixel = 0;
	if (ioctl(0, TIOCGWINSZ, &ws) < 0)
		vm_error("Failed to retrieve terminal size");
	*height = ws.ws_row;
	*width = ws.ws_col;
}

void		legend_authors(t_vm *core)
{
	int		x;
	int		y;
	int		len;
	char	*legends;

	legends = NULL;
	len = ft_strlen(L_CW_TITLE) + ft_strlen(L_ASOL) +\
			ft_strlen(L_JM) + ft_strlen(L_JN);
	if (core->vfx->legend->width < (int)(ft_strlen(L_CW_TITLE)\
		+ ft_strlen(L_AUTHOR_SHORT) + 2))
		return ;
	else if (core->vfx->legend->width < len + 2)
	{
		len = ft_strlen(L_CW_TITLE) + ft_strlen(L_AUTHOR_SHORT);
		legends = ft_strjoin(L_CW_TITLE, L_AUTHOR_SHORT);
	}
	x = core->vfx->legend->width / 2 - len / 2;
	y = core->vfx->legend->height - 2;
	wattron(core->vfx->legend->win, A_BOLD);
	if (legends)
	{
		mvwprintw(core->vfx->legend->win, y, x, legends);
		free(legends);
	}
	else
		mvwprintw(core->vfx->legend->win, y, x, "%s%s%s%s",\
			L_CW_TITLE, L_ASOL, L_JM, L_JN);
	wattroff(core->vfx->legend->win, A_BOLD);
}
