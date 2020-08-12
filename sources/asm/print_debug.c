/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 21:23:59 by jnovotny          #+#    #+#             */
/*   Updated: 2020/08/12 16:07:14 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	print_asmcore(t_asm *core)
{
	ft_printf("%{UNDERLINE}ASM Core%{EOC}\n");
	ft_printf("Source FD: %d\n", core->source_fd);
	ft_printf("Target FD: %d\n", core->core_fd);
	ft_printf("Champ's Name: %s\n", core->champ_name);
	ft_printf("Champ's Comment: %s\n", core->champ_comment);
}

/*
** Test printer to see the contents of the linked list.
*/

void	print_op(t_operation *list)
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
}

void	print_list(t_operation *list, t_asm *core)
{
	while (list != NULL)
	{
		print_op(list);
		list = list->next;
	}
	ft_printf("Total size in bytes: %d\n", core->byte_size);
	ft_printf("\n");
}
