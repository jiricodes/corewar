/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:17:47 by jnovotny          #+#    #+#             */
/*   Updated: 2020/07/20 15:03:28 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	vm_error(t_vm	*core, int error_id, char *extra)
{
	char	*custom_msg;

	
}

void	print_usage(void)
{
	ft_printf("Usage:\n");
	ft_printf("./corewar -[flag] [-n [player_number] [player.cor]] ...\n");
	ft_printf("\nFlags:\n");
	ft_printf("-n [number]\tFollowed by .cor file. Assign the number to the player");
	ft_printf("-d [number]\tDumps memory after that cycle.");
	ft_printf("-v\t\ttoggle visualiser");
}