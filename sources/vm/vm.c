/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 10:40:56 by jnovotny          #+#    #+#             */
/*   Updated: 2020/07/20 16:30:05 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static t_vm	*init_vm(void)
{
	t_vm	*core;

	core = (t_vm *)ft_memalloc(sizeof(t_vm));
	if (!core)
		ft_error_exit("Malloc at init_vm [core]", NULL, NULL);
	core->n_players = 0;
	core->champ = (t_champ **)ft_memalloc(sizeof(t_champ) * MAX_PLAYERS);
	if (!(core->champ))
		ft_error_exit("Malloc at init_vm [champ]", NULL, NULL);
	core->car_list = NULL;
	core->cycles_to_die = CYCLE_TO_DIE;
	core->check_cd = core->cycles_to_die;
	core->last_to_live = NULL;
	core->vfx_on = 0;
	core->dump_cycle = -1;
	core->dump_size = 0;
	return (core);
}

static void		clear_vm(t_vm *core)
{
	delete_champs(core->champ, core->n_players);
	delete_car_list(core->car_list);
	free(core->arena);
	free(core->byte_owner);
	if (VFX)
		free(core->vfx);
	free(core);
}

int main(int argc, char **argv)
{
	t_vm *core;
	int	i;
	ssize_t position;

	if (argc > 1 && argc <= MAX_PLAYERS + 1)
	{
		core = init_vm();
		init_arena(core);
		if (LOG)
			vm_log("Arena initialized\n");
		process_vm_args(core, argv, argc);
		engine(core);
		
	}
	clear_vm(core);
	// while(1);
	return (0);
}