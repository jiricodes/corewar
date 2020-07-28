/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_args.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 13:59:43 by jnovotny          #+#    #+#             */
/*   Updated: 2020/07/28 08:18:48 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			process_dump(t_vm *core, char *cycle, char *size)
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

static size_t	confirm_player_num(t_vm *core, char *number)
{
	size_t n;
	size_t i;

	i = 0;
	while (number[i] != '\0')
	{
		if (!ft_isdigit(number[i]))
			vm_error("Player number must be a positive number", F_LOG);
		i++;
	}
	n = (size_t)ft_latoi(number);
	if (!check_player_id(core, n, 1))
		vm_error("ID already taken", F_LOG);
	return (n);
}

void			process_player(t_vm *core, char *number, char *filename)
{
	size_t	n;
	size_t	i;
	ssize_t	position;

	if (number)
		n = confirm_player_num(core, number);
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

void			process_vm_args(t_vm *core, char **argv, int argc)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		i += handle_flags(core, argv, argc, i);
		i++;
	}
}
