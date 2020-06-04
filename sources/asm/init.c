/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 10:57:41 by jnovotny          #+#    #+#             */
/*   Updated: 2020/06/04 13:03:41 by jnovotny         ###   ########.fr       */
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
		ft_error_exit("Given file is of incorrect type", core, clear_t_asm);
	core->source_fd = open(filename, O_RDONLY);
	if (core->source_fd < 0)
		ft_error_exit("Failed to open given source file", core, clear_t_asm);
	core->core_fd = open(target_file, O_RDWR);
	if (core->core_fd < 0)
		ft_error_exit("Failed to open given source file", core, clear_t_asm);
	return (core);
}
