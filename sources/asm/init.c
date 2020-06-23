/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 10:57:41 by jnovotny          #+#    #+#             */
/*   Updated: 2020/06/09 11:20:34 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_asm	*intialize_asm(char *filename)
{
	t_asm	*core;
	char	*target_file;

	core = (t_asm *)ft_memalloc(sizeof(t_asm));
	if (!core)
		ft_error_exit("Malloc at initialize_asm", NULL, NULL);
	target_file = filename_pars(filename, SRC_TYPE, TRGT_TYPE);
	if (!target_file)
		ft_error_exit("Given file is of incorrect type", (void *)core, clear_t_asm);
	core->source_fd = open(filename, O_RDONLY);
	if (core->source_fd < 0)
		ft_error_exit("Failed to open given source file", (void *)core, clear_t_asm);
	core->core_fd = open(target_file, O_RDWR | O_CREAT, 0600);
	if (core->core_fd < 0)
		ft_error_exit("Failed to open given target file", (void *)core, clear_t_asm);
	core->flag = 0;
	return (core);
}

/*
** Function to add a node to the linked list struct.
** Allocates memory and initializes all values to null.
*/

t_operation	*newnode(void)
{
	t_operation *new;

	new = (t_operation*)ft_memalloc(sizeof(t_operation));
	if (!new)
		ft_error_exit("Malloc at newnode", NULL, NULL);
	new->label = NULL;
	new->operation = NULL;
	new->arg[0] = NULL;
	new->arg[1] = NULL;
	new->arg[2] = NULL;
	new->next = NULL;
	new->op_size = NULL;
	new->t_dir_size = 0;
	return (new);
}

/*
** Function to append a new link to the end of the list
** Goes through the list and calls for newnode to allocate and initialize the new node.
*/

int	list_append(t_operation **head)
{
	t_operation *last;

	last = *head;
	if (*head == NULL)
	{
		*head = newnode();
		return (1);
	}
	while (last->next != NULL)
		last = last->next;
	last->next = newnode();
	return (1);
}
