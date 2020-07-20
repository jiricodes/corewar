/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carriage.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 16:08:23 by jnovotny          #+#    #+#             */
/*   Updated: 2020/07/20 17:10:38 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static t_args	*car_init_args(void)
{
	int		cnt;
	t_args	*new;
	cnt = 0;
	new = (t_args *)ft_memalloc(sizeof(t_args));
	if (!new)
		ft_error_exit("Malloc at init_args", NULL, NULL);
	return (new);
}

t_car	*create_carriage(size_t id, ssize_t	pc, uint8_t player_id)
{
	t_car	*car;

	car = (t_car *)ft_memalloc(sizeof(t_car));
	if (!car)
		ft_error_exit("Malloc at create_carriage", NULL, NULL);
	car->id = id;
	ft_bzero(car->reg, sizeof(int32_t) * REG_NUMBER);
	car->reg[0] = -1 * player_id;
	car->carry = 0;
	car->pc = pc;
	car->step = 1;
	car->op_index = -1;
	car->cooldown = 0;
	car->last_live = 1;
	car->args = car_init_args();
	car->next = NULL;
	return (car);
}

t_car	*prepend_carriage(t_car *head, t_car *node)
{
	node->next = head;
	return (node);
}

t_car	*append_carriage(t_car *head, t_car *node)
{
	t_car	*temp;

	if (!head)
		return (node);
	temp = head;
	while (temp->next)
		temp = temp->next;
	temp->next = node;
	return (head);
}

t_car	*delete_carriage(t_car *head, size_t id)
{
	t_car	*temp;
	t_car	*tbd;

	if (!head)
		return (NULL);
	if (head->id == id)
	{
		tbd = head;
		head = head->next;
		free(tbd->args);
		free(tbd);
		return (head);
	}
	temp = head;
	while (temp->next)
	{
		if (temp->next->id == id)
		{
			tbd = temp->next;
			temp->next = tbd->next;
			free(tbd->args);
			free(tbd);
			break;
		}
		temp = temp->next;
	}
	return (head);
}

void	delete_car_list(t_car *head)
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
