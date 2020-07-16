/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 10:24:21 by jnovotny          #+#    #+#             */
/*   Updated: 2020/07/16 18:39:14 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

#include <stdio.h>
#include <stdarg.h>

void		vm_log(char *message, ...)
{
	va_list	args;
	va_list args2;
	FILE	*log_file;

	log_file = fopen(LOG_FILE, "a+");
	va_start(args, message);
	vfprintf(log_file, message, args);
	if (LOG == 2)
	{
		va_start(args2, message);
		vprintf(message, args2);
		va_end(args2);
	}
	va_end(args);
	fclose(log_file);
}

void		log_carriage(t_car *node)
{
	vm_log("Carriage [%zu]\nPC\t%zd\nOP\t%d\nCD\t%zu\n\n", node->id, node->pc, node->op_index, node->cooldown);
}