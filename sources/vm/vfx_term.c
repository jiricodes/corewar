/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vfx_term.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 08:13:58 by jnovotny          #+#    #+#             */
/*   Updated: 2020/08/07 08:14:13 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

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
