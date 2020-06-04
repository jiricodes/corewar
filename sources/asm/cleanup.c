/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 11:20:45 by jnovotny          #+#    #+#             */
/*   Updated: 2020/06/04 13:06:49 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	clear_t_asm(t_asm *object)
{
	if (object->source_fd > 2)
		if (close(object->source_fd) < 0)
			ft_error_exit("Failed to close source file", NULL, NULL);
	if (object->core_fd > 2)
		if (close(object->core_fd) < 0)
			t_error_exit("Failed to close target file", NULL, NULL);
	free(object);
}