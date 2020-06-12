/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_colors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 14:57:21 by jnovotny          #+#    #+#             */
/*   Updated: 2020/06/12 15:53:51 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	vfx_colors()
{
	start_color();
	init_pair(1, COLOR_RED, 0);
	init_pair(2, COLOR_BLUE, 0);
	init_pair(3, COLOR_GREEN, 0);
	init_pair(4, COLOR_YELLOW, 0);
	init_pair(5, COLOR_MAGENTA, 0);
	init_pair(6, COLOR_CYAN, 0);
}