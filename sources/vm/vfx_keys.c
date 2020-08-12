/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vfx_keys.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 17:43:04 by jnovotny          #+#    #+#             */
/*   Updated: 2020/08/12 17:45:47 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		keys2(t_vm *core)
{
	if (core->vfx->key == KEY_LEFT)
	{
		core->vfx->freq += VFX_SPEED_DELTA;
		draw_legend(core);
	}
	else if (core->vfx->key == 's')
	{
		core->vfx->play = 0;
		vfx_cycle(core);
	}
}

void			vfx_key(t_vm *core)
{
	if (core->vfx->key == ' ')
	{
		core->vfx->play = core->vfx->play ? 0 : 1;
		draw_cycle(core);
	}
	else if (core->vfx->key == 27)
	{
		endwin();
		free_vfx(core);
		clear_vm(core);
		exit(0);
	}
	else if (core->vfx->key == KEY_RIGHT)
	{
		core->vfx->freq = core->vfx->freq > VFX_SPEED_DELTA ?\
			core->vfx->freq - VFX_SPEED_DELTA : 1;
		draw_legend(core);
	}
	else
		keys2(core);
}
