/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_args_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 07:55:08 by jnovotny          #+#    #+#             */
/*   Updated: 2020/08/03 14:26:26 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

size_t			find_player_nb(t_vm *core, size_t start)
{
	size_t n;

	n = start;
	while (!check_player_id(core, n, 0))
		n++;
	return (n);
}

size_t			check_player_id(t_vm *core, size_t number, int8_t mod)
{
	int		i;
	size_t	tmp;

	i = 0;
	if (number > PLAYER_N_MAX || number < 1)
		vm_error("Champion's number must be 0 < N <= PLAYER_N_MAX");
	while (i < core->n_players)
	{
		if (core->champ[i]->id == number)
		{
			if (core->champ[i]->usr_id == 0 && mod)
			{
				tmp = find_player_nb(core, 1);
				core->champ[i]->id = tmp == number ?\
					find_player_nb(core, number + 1) : tmp;
				return (number);
			}
			else
				return (0);
		}
		i++;
	}
	return (number);
}
