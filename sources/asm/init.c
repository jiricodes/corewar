/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 10:57:41 by jnovotny          #+#    #+#             */
/*   Updated: 2020/07/13 13:38:23 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_asm			*intialize_asm(char *filename)
{
	t_asm	*core;
	char	*target_file;

	core = (t_asm *)ft_memalloc(sizeof(t_asm));
	if (!core)
		ft_error_exit("Malloc at initialize_asm", NULL, NULL);
	core->target_file = filename_pars(filename, SRC_TYPE, TRGT_TYPE);
	if (!core->target_file)
		ft_error_exit("Incorrect file type", (void *)core, clear_t_asm);
	core->source_fd = open(filename, O_RDONLY);
	if (core->source_fd < 0)
		ft_error_exit("Open Error on source file", (void *)core, clear_t_asm);
	core->byte_size = 0;
	core->line_cnt = 0;
	return (core);
}

/*
** Function to add a node to the linked list struct.
** Allocates memory and initializes all values to null.
*/

t_operation		*newnode(void)
{
	t_operation *new;

	new = (t_operation*)ft_memalloc(sizeof(t_operation));
	if (!new)
		ft_error_exit("Malloc at newnode", NULL, NULL);
	new->label = NULL;
	new->op_name = NULL;
	new->arg[0] = NULL;
	new->arg[1] = NULL;
	new->arg[2] = NULL;
	new->argtypes[0] = 0;
	new->argtypes[1] = 0;
	new->argtypes[2] = 0;
	new->next = NULL;
	new->op_size = 0;
	new->t_dir_size = 0;
	new->op_code = 0;
	new->position = 0;
	new->label_pos[0] = 0;
	new->label_pos[1] = 0;
	new->label_pos[2] = 0;
	return (new);
}

/*
** Function to append a new link to the end of the list
** Goes through the list and calls for newnode to allocate
** and initialize the new node.
*/

int				list_append(t_operation **head)
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

/*
** Test printer to see the contents of the linked list.
*/

void			print_list(t_operation *list, t_asm *core)
{
	while (list != NULL)
	{
		ft_printf("\nlabel: %s, position: %d\n", list->label, list->position);
		ft_printf("operation: %s\n", list->op_name);
		ft_printf("arg1: %s\n", list->arg[0]);
		ft_printf("arg2: %s\n", list->arg[1]);
		ft_printf("arg3: %s\n", list->arg[2]);
		ft_printf("labelpos1: %d\n", list->label_pos[0]);
		ft_printf("labelpos2: %d\n", list->label_pos[1]);
		ft_printf("labelpos3: %d\n", list->label_pos[2]);
		ft_printf("op_size: %d\n", list->op_size);
		ft_printf("t_dir_size: %d\n", list->t_dir_size);
		ft_printf("arg1 TYPE: %d\n", list->argtypes[0]);
		ft_printf("arg2 TYPE: %d\n", list->argtypes[1]);
		ft_printf("arg3 TYPE: %d\n", list->argtypes[2]);
		ft_printf("has arg type code?: %d\n", list->arg_type_code);
		list = list->next;
	}
	ft_printf("Total size in bytes: %d\n", core->byte_size);
	ft_printf("\n");
}
