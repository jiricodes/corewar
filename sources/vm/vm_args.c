/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_args.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 13:59:43 by jnovotny          #+#    #+#             */
/*   Updated: 2020/07/20 16:33:52 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"


static void	process_dump(t_vm *core, char *cycle, char *size)
{
	size_t i;

	i = 0;
	while (cycle[i] != '\0')
	{
		if (!ft_isdigit(cycle[i]))
			ft_error_exit("Dump cycle must be a positive number", NULL, NULL);
		i++;
	}
	core->dump_cycle = (ssize_t)ft_latoi(cycle);
	core->dump_size = ft_strequ(size, "-d") ? 32 : 64;
}

static int		check_player_id(t_vm *core, size_t number)
{
	int i;

	i = 0;
	if (number > 255)
		ft_error_exit("Champion's number must be 0 < X <= 255", NULL, NULL);
	while (i < core->n_players)
	{
		if (core->champ[i]->id == number)
			return (0);
		i++;
	}
	return (1);
}

static size_t	find_player_nb(t_vm *core)
{
	
	size_t n;

	n = 1;
	while (!check_player_id(core, n))
		n++;
	return (n);
}

static void	process_player(t_vm *core, char *number, char *filename)
{
	size_t n;
	size_t i;
	ssize_t position;

	i = 0;
	if (number)
	{
		while (number[i] != '\0')
		{
			if (!ft_isdigit(number[i]))
				ft_error_exit("Player number must be a positive number", NULL, NULL);
			i++;
		}
		n = (size_t)ft_latoi(number);
		if (!check_player_id(core, n))
			ft_error_exit("ID already taken", NULL, NULL);
		// needs revisit (if one player is assigned a number that was assigned automatically they need to be "swapped")
	}
	else
		n = find_player_nb(core);
	i = core->n_players;
	core->n_players++;
	core->champ[i] = init_champ(filename, (uint8_t)n);
	load_champ(core->champ[i]);
	if (LOG)
		vm_log("Champ [%zu] initialized and loaded\n", n);
	position = i * MEM_SIZE / core->n_players;
	insert_champ_to_arena(core, core->champ[i], position);
	if (LOG)
		vm_log("Champ [%zu] inserted to arena\n", n);
	core->car_list = prepend_carriage(core->car_list, create_carriage(core->car_id, position, (uint8_t)n));
	core->car_id++;
}

/*
** Deals with flags and arguments
*/

void	process_vm_args(t_vm *core, char **argv, int argc)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (ft_strequ(argv[i], "-dump") || ft_strequ(argv[i], "-d"))
		{
			if (i < argc - 1)
				process_dump(core, argv[i + 1], argv[i]);
			else
				ft_error_exit("Dump flag missing a value", NULL, NULL);
			i++;
		}
		else if (ft_strequ(argv[i], "-v"))
			core->vfx_on = 1;
		else if (ft_strequ(argv[i], "-n"))
		{
			if (i < argc - 2)
				process_player(core, argv[i + 1], argv[i + 2]);
			else
				ft_error_exit("Player manual numbering error", NULL, NULL);
			i += 2;
		}
		else
			process_player(core, NULL, argv[i]);
		i++;
	}
}