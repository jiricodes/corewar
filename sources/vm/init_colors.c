/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_colors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 14:57:21 by jnovotny          #+#    #+#             */
/*   Updated: 2020/07/26 16:52:24 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	vfx_colors(void)
{
	start_color();
	init_color(8, 355, 355, 355);
	init_color(9, 1000, 1000, 1000);
	init_pair(1, COLOR_RED, 0);
	init_pair(2, COLOR_BLUE, 0);
	init_pair(3, COLOR_GREEN, 0);
	init_pair(4, COLOR_YELLOW, 0);
	init_pair(5, COLOR_MAGENTA, 0);
	init_pair(6, COLOR_CYAN, 0);
	init_pair(7, COLOR_WHITE, 0);
	init_pair(8, 8, 0);
	init_pair(9, 9, 0);
}
