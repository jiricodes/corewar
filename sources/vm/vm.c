/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 10:40:56 by jnovotny          #+#    #+#             */
/*   Updated: 2020/06/12 16:03:18 by jnovotny         ###   ########.fr       */
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
	return (core);
}

int main(int argc, char **argv)
{
	t_vm *core;
	int	i;

	if (argc > 1 && argc < 8)
	{
		core = init_vm(argc - 1);
		ft_printf("Number of players: %d\n", core->n_players);
		i = 0;
		init_arena(core);
		ft_printf("Arena initialized\n");
		while (i < core->n_players)
		{
			core->champ[i] = init_champ(argv[i + 1], i + 1);
			load_champ(core->champ[i]);
			ft_printf("Champ [%d] initialized and loaded\n", i + 1);
			insert_champ_to_arena(core, core->champ[i], i * MEM_SIZE / core->n_players);
			ft_printf("Champ [%d] inserted to arena\n", i + 1);
			i++;
		}
		show_arena(core);
		ft_printf("Exited visual window\n");
	}
	// while(1);
	return (0);
}