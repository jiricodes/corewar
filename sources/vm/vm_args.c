/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_args.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 13:59:43 by jnovotny          #+#    #+#             */
/*   Updated: 2020/07/27 17:40:05 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"


static void		process_dump(t_vm *core, char *cycle, char *size)
{
	size_t i;

	i = 0;
	while (cycle[i] != '\0')
	{
		if (!ft_isdigit(cycle[i]))
			vm_error("Dump cycle must be a positive number", F_LOG);
		i++;
	}
	core->flags->dump_cycle = (size_t)ft_latoi(cycle);
	core->flags->dump_size = ft_strequ(size, "-d") ? 64 : 32;
}

static size_t	find_player_nb(t_vm *core, size_t start)
{
	
	size_t n;

	n = start;
	while (!check_player_id(core, n, 0))
		n++;
	return (n);
}

size_t		check_player_id(t_vm *core, size_t number, int8_t mod)
{
	int		i;
	size_t	tmp;
	char	*buf;

	i = 0;
	if (number > PLAYER_N_MAX || number < 1)
	{
		ft_sprintf(buf, "Champion's number must be 0 < N <= %zu", PLAYER_N_MAX);
		vm_error(buf, F_LOG);
	}
	while (i < core->n_players)
	{
		if (core->champ[i]->id == number)
		{
			if (core->champ[i]->usr_id == 0 && mod)
			{
				tmp = find_player_nb(core, 1);
				core->champ[i]->id = tmp == number ? find_player_nb(core, number + 1) : tmp;
				return (number);
			}
			else
				return (0);
		}
		i++;
	}
	return (number);
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
				vm_error("Player number must be a positive number", F_LOG);
			i++;
		}
		n = (size_t)ft_latoi(number);
		if (!check_player_id(core, n, 1))
			vm_error("ID already taken", F_LOG);
	}
	else
		n = find_player_nb(core, 1);
	i = core->n_players;
	core->n_players++;
	if (i >= MAX_PLAYERS)
		vm_error("Too many players.", F_LOG);
	core->champ[i] = init_champ(filename, (uint8_t)n);
	if (number)
		core->champ[i]->usr_id = 1;
	load_champ(core->champ[i]);
	vm_log(F_LOG, "Champ [%zu] initialized and loaded\n", n);
}

/*
** Deals with flags and arguments
*/

static int		handle_flags(t_vm *core, char **argv, int argc, int i)
{
	if (ft_strequ(argv[i], "-dump") || ft_strequ(argv[i], "-d"))
	{
		process_dump(core, i < argc - 1 ? argv[i + 1] : "0", argv[i]);
		return (1);
	}
	else if (ft_strequ(argv[i], "-v"))
	{
		core->flags->vfx = 1;
		core->flags->silent = 1;
	}
	else if (ft_strequ(argv[i], "-n"))
	{
		if (i < argc - 2)
			process_player(core, argv[i + 1], argv[i + 2]);
		else
			vm_error("Player manual numbering error", core->flags->log);
		return (2);
	}
	else if (ft_strequ(argv[i], "-log") && i < argc - 1 && ft_strlen(argv[i + 1]) == 1 && ft_strchr(F_LOG_STR, argv[i + 1][0]))
	{
		core->flags->log = argv[i + 1][0] - 48;
		return (1);
	}
	else if (ft_strequ(argv[i], "-a"))
		core->flags->aff = 1;
	else if (ft_strequ(argv[i], "-s"))
		core->flags->silent = 1;
	// else if (ft_strequ(argv[i], ""))
	// 	return (0);
	else
		process_player(core, NULL, argv[i]);
	return (0);
}

void	process_vm_args(t_vm *core, char **argv, int argc)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		i += handle_flags(core, argv, argc, i);
		i++;
	}
}