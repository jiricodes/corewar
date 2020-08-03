/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:17:47 by jnovotny          #+#    #+#             */
/*   Updated: 2020/08/03 14:36:37 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	vm_error(char *usr_msg)
{
	if (errno != 0)
		perror("SYSTEM ERROR: ");
	if (usr_msg)
		ft_dprintf(2, "VM ERROR: %s\n", usr_msg);
	exit(-1);
}

void	print_usage(void)
{
	ft_printf("Usage:\n\n");
	ft_printf("./corewar -[flag] [-n [player_number] [player.cor]] ...\n");
	ft_printf("\nFlags:\n");
	ft_printf("-n [number] <player.cor>\tAssign the number to the player\n");
	ft_printf("-d [number]\t\t\tDumps memory after that cycle. 64 octets\n");
	ft_printf("-dump [number]\t\t\tDumps memory after that cycle. 32 octets\n");
	ft_printf("-v\t\t\t\ttoggle visualiser\n");
	ft_printf("-a\t\t\t\taff support\n");
	ft_printf("-log [number]\n");
	ft_printf("\t\t\t\t%d - operations, includes cycle\n", LOG_OPS);
	ft_printf("\t\t\t\t%d - details\n", LOG_DETAILS);
	ft_printf("-s\t\t\t\tsilent run\n");
}
