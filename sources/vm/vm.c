/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 10:40:56 by jnovotny          #+#    #+#             */
/*   Updated: 2020/08/10 15:27:30 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static t_vm	*init_vm(void)
{
	t_vm	*core;

	core = (t_vm *)ft_memalloc(sizeof(t_vm));
	if (!core)
		vm_error("Malloc at init_vm [core]");
	core->n_players = 0;
	core->champ = (t_champ **)ft_memalloc(sizeof(t_champ) * MAX_PLAYERS);
	if (!(core->champ))
		vm_error("Malloc at init_vm [champ]");
	core->flags = (t_flg *)ft_memalloc(sizeof(t_flg));
	if (!core->flags)
		vm_error("Malloc at init_vm [flags]");
	core->flags->large = CHAMP_MAX_SIZE;
	core->cycles_to_die = CYCLE_TO_DIE;
	core->check_cd = core->cycles_to_die;
	core->flags->dump_cycle = -1;
	core->flags->log = LOG;
	core->checks = 0;
	core->car_id = 1;
	return (core);
}

void		clear_vm(t_vm *core)
{
	delete_champs(core->champ, core->n_players);
	delete_car_list(core->car_list);
	if (core->arena)
		free(core->arena);
	if (core->byte_owner)
		free(core->byte_owner);
	if (core->flags)
		free(core->flags);
	free(core);
}

int			main(int argc, char **argv)
{
	t_vm *core;

	if (argc > 1)
	{
		core = init_vm();
		init_arena(core);
		process_vm_args(core, argv, argc);
		introduce_champs(core);
		if (core->flags->vfx)
			vfx_engine(core);
		else
			engine(core);
		if (core->flags->log & LOG_DETAILS)
			log_vm_status(core);
		clear_vm(core);
	}
	else
		print_usage();
	return (0);
}
