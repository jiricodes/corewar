/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 10:24:21 by jnovotny          #+#    #+#             */
/*   Updated: 2020/08/04 17:58:39 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

#include <stdio.h>
#include <stdarg.h>

void		log_carriage(t_car *node)
{
	int i;

	i = 0;
	ft_printf("Carriage [%zu]\nPC\t%zd\nOP\t%d\nCD\t%zu\n",\
		node->id, node->pc, node->op_index, node->cooldown);
	ft_printf("REG: ");
	while (i++ < REG_NUMBER)
		ft_printf(" %d |", node->reg[i - 1]);
	ft_printf("\nCarry\t%d\n", node->carry);
	ft_printf("Last Live\t%zu\n\n", node->last_live);
}

void		log_champ(t_champ *champ, int index)
{
	int i;

	ft_printf("Champ[%d] Details:\n", index);
	ft_printf("ID\t\t%5zu\n", champ->id);
	ft_printf("User\t\t%5d\n", champ->usr_id);
	ft_printf("FD\t\t%5d\n", champ->fd);
	ft_printf("Name\t\t%s\n", champ->header->prog_name);
	ft_printf("Size\t\t%5u\n\n", champ->header->prog_size);
	i = 0;
}

void		log_vm_status(t_vm *core)
{
	int		i;
	t_car	*tmp;
	size_t	limit;

	ft_printf("Virtual Machine Details:\n");
	ft_printf("Players\t%5d\n", core->n_players);
	ft_printf("Cycle\t\t%5zu\n", core->cycle);
	ft_printf("CTD\t\t%5zd\n", core->cycles_to_die);
	limit = core->cycle + core->check_cd - core->cycles_to_die;
	ft_printf("Llim\t\t%5zu\n", limit);
	ft_printf("NBR_LIVE\t%5d\n", core->live_cnt);
	ft_printf("MAX_CHECKS\t%5d\n\n", core->checks);
	i = 0;
	while (i < core->n_players)
	{
		log_champ(core->champ[i], i);
		i++;
	}
	tmp = core->car_list;
	while (tmp)
	{
		log_carriage(tmp);
		tmp = tmp->next;
	}
	ft_printf("Total Car:\t%5d\n\n", core->car_cnt);
}

void		log_arena(uint8_t *arena, int size)
{
	int	i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (i != 0 && i % size == 0)
			ft_printf("\n");
		if (i % size == 0)
			ft_printf("%#06x :", i);
		ft_printf(" %02x", arena[i]);
		i++;
	}
	ft_printf("\n");
}
