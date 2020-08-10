/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:17:47 by jnovotny          #+#    #+#             */
/*   Updated: 2020/08/10 15:09:35 by jnovotny         ###   ########.fr       */
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
	ft_printf("-n [number] <player.cor>\tAssign number n to the player\n");
	ft_printf("-d [number]\t\t\tDumps memory after that cycle. 64 octets\n");
	ft_printf("-dump [number]\t\t\tDumps memory after that cycle. 32 octets\n");
	ft_printf("-v\t\t\t\ttoggle visualiser (supports -log 1 flag)\n");
	ft_printf("-a\t\t\t\taff support\n\n");
	ft_printf("-log [number]\t\t\tCan be added together for multiple\n");
	ft_printf("\t\t\t\t%d - operations, includes cycle\n", LOG_OPS);
	ft_printf("\t\t\t\t%d - details\n", LOG_DETAILS);
	ft_printf("\t\t\t\t%d - deaths\n", LOG_DEATHS);
	ft_printf("\t\t\t\t%d - cycle to die changes\n", LOG_CTD);
	ft_printf("\t\t\t\t%d - fork & lfork info\n", LOG_COPY_CAR);
	ft_printf("\t\t\t\t%d - Carriage movement\n", LOG_PC);
	ft_printf("\t\t\t\t%d - Carriage Count\n\n", LOG_CAR_CNT);
	ft_printf("-s\t\t\t\tsilent run\n");
	ft_printf("-l\t\t\t\tsets champs max size = MEM_SIZE / MAX_PLAYERS\n");
}
