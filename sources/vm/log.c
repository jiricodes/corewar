/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 10:24:21 by jnovotny          #+#    #+#             */
/*   Updated: 2020/07/27 13:22:06 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

#include <stdio.h>
#include <stdarg.h>

void		vm_log(uint8_t lvl, char *message, ...)
{
	va_list	args;
	va_list args2;
	FILE	*log_file;

	if (lvl)
	{
		log_file = fopen(LOG_FILE, "a+");
		va_start(args, message);
		vfprintf(log_file, message, args);
		if (lvl == 2)
		{
			va_start(args2, message);
			vprintf(message, args2);
			va_end(args2);
		}
		va_end(args);
		fclose(log_file);
	}
}

void		log_carriage(t_car *node, uint8_t log_lvl)
{
	int i;

	i = 0;
	vm_log(log_lvl, "Carriage [%zu]\nPC\t%zd\nOP\t%d\nCD\t%zu\n",\
		node->id, node->pc, node->op_index, node->cooldown);
	vm_log(log_lvl, "REG: ");
	while (i++ < REG_NUMBER)
		vm_log(log_lvl, " %d |", node->reg[i - 1]);
	vm_log(log_lvl, "\nCarry\t%d\n", node->carry);
	vm_log(log_lvl, "Last Live\t%zu\n\n", node->last_live);
}

void		log_champ(t_champ *champ, int index, uint8_t log_lvl)
{
	vm_log(log_lvl, "Champ[%d] Details:\n", index);
	vm_log(log_lvl, "ID\t\t%5zu\n", champ->id);
	vm_log(log_lvl, "User\t\t%5d\n", champ->usr_id);
	vm_log(log_lvl, "FD\t\t%5d\n", champ->fd);
	vm_log(log_lvl, "Name\t\t%s\n", champ->header->prog_name);
	vm_log(log_lvl, "Size\t\t%5u\n\n", champ->header->prog_size);
}

void		log_vm_status(t_vm *core, uint8_t log_lvl)
{
	int		i;
	t_car	*tmp;
	size_t	limit;

	vm_log(log_lvl, "Virtual Machine Details:\n");
	vm_log(log_lvl, "Players\t%5d\n", core->n_players);
	vm_log(log_lvl, "Cycle\t\t%5zu\n", core->cycle);
	vm_log(log_lvl, "CTD\t\t%5zd\n", core->cycles_to_die);
	limit = core->cycle + core->check_cd - core->cycles_to_die;
	vm_log(log_lvl, "Llim\t\t%5zu\n", limit);
	i = 0;
	while (i < core->n_players)
	{
		log_champ(core->champ[i], i, log_lvl);
		i++;
	}
	tmp = core->car_list;
	i = 0;
	while (tmp)
	{
		log_carriage(tmp, log_lvl);
		tmp = tmp->next;
		i++;
	}
	vm_log(log_lvl, "Total Car:\t%5d\n\n", i);
}

void			log_arena(uint8_t *arena, int size, uint8_t log_lvl)
{
	int	i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (i != 0 && i % size == 0)
			vm_log(log_lvl, "\n");
		if (i % size == 0)
			vm_log(log_lvl, "%#06x :", i);
		else
			vm_log(log_lvl, " %02x", arena[i]);
		i++;
	}
	vm_log(log_lvl, "\n");
}
