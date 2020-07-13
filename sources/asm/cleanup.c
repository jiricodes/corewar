/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 11:20:45 by jnovotny          #+#    #+#             */
/*   Updated: 2020/07/13 13:38:19 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	clear_t_asm(void *object)
{
	if (((t_asm*)object)->source_fd > 2)
		if (close(((t_asm*)object)->source_fd) < 0)
			ft_error_exit("Failed to close source file", NULL, NULL);
	if (((t_asm*)object)->core_fd > 2)
		if (close(((t_asm*)object)->core_fd) < 0)
			ft_error_exit("Failed to close target file", NULL, NULL);
	if (((t_asm*)object)->champ_name)
		free(((t_asm*)object)->champ_name);
	if (((t_asm*)object)->champ_comment)
		free(((t_asm*)object)->champ_comment);
	if (((t_asm*)object)->target_file)
		free(((t_asm*)object)->target_file);
	free(object);
}