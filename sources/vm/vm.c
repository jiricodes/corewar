/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 10:40:56 by jnovotny          #+#    #+#             */
/*   Updated: 2020/07/20 13:45:22 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static t_vm	*init_vm(int	n_players)
{
	t_vm	*core;

	core = (t_vm *)ft_memalloc(sizeof(t_vm));
	if (!core)
		ft_error_exit("Malloc at init_vm [core]", NULL, NULL);
	core->n_players = n_players;
	core->champ = (t_champ **)ft_memalloc(sizeof(t_champ) * n_players);
	if (!(core->champ))
		ft_error_exit("Malloc at init_vm [champ]", NULL, NULL);
	core->car_list = NULL;
	core->cycles_to_die = CYCLE_TO_DIE;
	core->check_cd = core->cycles_to_die;
	core->last_to_live = NULL;
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
		core = init_vm(argc - 1);
		vm_log("Number of players: %d\n", core->n_players);
		i = 0;
		init_arena(core);
		vm_log("Arena initialized\n");
		while (i < core->n_players)
		{
			core->champ[i] = init_champ(argv[i + 1], i + 1);
			load_champ(core->champ[i]);
			vm_log("Champ [%d] initialized and loaded\n", i + 1);
			position = i * MEM_SIZE / core->n_players;
			insert_champ_to_arena(core, core->champ[i], position);
			vm_log("Champ [%d] inserted to arena\n", i + 1);
			core->car_list = prepend_carriage(core->car_list, create_carriage(core->car_id, position, (uint8_t)i));
			core->car_id++;
			i++;
		}
		engine(core);
		
	}
	clear_vm(core);
	while(1);
	return (0);
}