/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_colors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 14:57:21 by jnovotny          #+#    #+#             */
/*   Updated: 2020/08/06 13:28:19 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	vfx_colors(void)
{
	start_color();
	use_default_colors();
	init_color(8, 355, 355, 355);
	init_color(9, 1000, 1000, 1000);
	init_color(10, 1000, 500, 0);
	init_pair(1, COLOR_RED, -1);
	init_pair(2, COLOR_BLUE, -1);
	init_pair(3, COLOR_GREEN, -1);
	init_pair(5, COLOR_YELLOW, -1);
	init_pair(4, COLOR_MAGENTA, -1);
	init_pair(6, COLOR_CYAN, -1);
	init_pair(7, COLOR_WHITE, -1);
	init_pair(8, 8, -1);
	init_pair(9, 9, -1);
	init_pair(10, 10, -1);
}
