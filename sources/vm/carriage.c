/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carriage.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 16:08:23 by jnovotny          #+#    #+#             */
/*   Updated: 2020/07/24 17:26:54 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_car			*create_carriage(size_t id, ssize_t pc, uint8_t player_id)
{
	t_car	*car;

	car = (t_car *)ft_memalloc(sizeof(t_car));
	if (!car)
		vm_error("Malloc at create_carriage", LOG);
	car->id = id;
	ft_bzero(car->reg, sizeof(int32_t) * REG_NUMBER);
	car->reg[0] = -1 * player_id;
	car->pc = pc;
	car->step = 1;
	car->op_index = -1;
	car->args = (t_args *)ft_memalloc(sizeof(t_args));
	if (!(car->args))
		vm_error("Malloc at car_init_args", LOG);
	car->next = NULL;
	return (car);
}

t_car			*prepend_carriage(t_car *head, t_car *node)
{
	node->next = head;
	return (node);
}

static void		del_node(t_car *node)
{
	free(node->args);
	free(node);
}

t_car			*delete_carriage(t_car *head, size_t id)
{
	t_car	*temp;
	t_car	*tbd;

	if (!head)
		return (NULL);
	if (head->id == id)
	{
		tbd = head;
		head = head->next;
		del_node(tbd);
		return (head);
	}
	temp = head;
	while (temp->next)
	{
		if (temp->next->id == id)
		{
			tbd = temp->next;
			temp->next = tbd->next;
			del_node(tbd);
			break ;
		}
		temp = temp->next;
	}
	return (head);
}

void			delete_car_list(t_car *head)
{
	t_car	*temp;

	while (head)
	{
		temp = head;
		head = temp->next;
		free(temp->args);
		free(temp);
	}
}
