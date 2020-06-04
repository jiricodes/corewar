/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 20:22:38 by jnovotny          #+#    #+#             */
/*   Updated: 2020/06/04 12:11:27 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_error.h"

/*
**	This function writes and error output and exits a program
**	after clearing the memory.
**
**	Parametres:
**	user_msg:	string containing a message from user to be output on stdout
**	memory:		pointer to a mememory to be cleared
**	del:		pointer to a function that clears given memory
*/

void	ft_error_exit(char *user_msg, void *memory, void (*del)(void *))
{
	if (memory != NULL)
	{
		if (del)
			del(memory);
		else
		{
			ft_printf("{RED}{B}MEMORY ERROR{EOC}: Memory (%p) not cleaned.",\
			memory);
			ft_printf("Clearing function not found!\n");
		}
	}
	if (errno != 0)
		perror("SYSTEM ERROR MESSAGE: ");
	if (user_msg)
		ft_printf("{RED}{B}USER ERROR MESSAGE{EOC}: %s\n", user_msg);
	exit(-1);
}
