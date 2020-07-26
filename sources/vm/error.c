/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:17:47 by jnovotny          #+#    #+#             */
/*   Updated: 2020/07/26 15:37:54 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	vm_error(char *usr_msg, uint8_t log)
{
	char *tmp;

	if (log)
	{
		if (errno != 0)
			vm_log(log ? 1 : 0, "SYSTEM ERROR DETAILS:\n%d\t%s\n",
				errno, strerror(errno));
		vm_log(0, "VM ERROR DETAILS:\n%s\n", usr_msg);
	}
	if (errno != 0)
		perror("SYSTEM ERROR: ");
	if (usr_msg)
		ft_dprintf(2, "VM ERROR: %s\n", usr_msg);
	exit(-1);
}

void	print_usage(void)
{
	ft_printf("Usage:\n");
	ft_printf("./corewar -[flag] [-n [player_number] [player.cor]] ...\n");
	ft_printf("\nFlags:\n");
	ft_printf("-n [number] <player.cor>\tAssign the number to the player");
	ft_printf("-d [number]\tDumps memory after that cycle. 64 octets");
	ft_printf("-dump [number]\tDumps memory after that cycle. 32 octets");
	ft_printf("-v\t\ttoggle visualiser");
	ft_printf("-a\t\taff support");
	ft_printf("-log [1 | 2]\t\ttoggle log 1 file, 2 file & stdout");
	ft_printf("-s\t\tsilent run");
}
