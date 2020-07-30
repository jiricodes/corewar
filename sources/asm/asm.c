/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolopov <asolopov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 10:51:34 by jnovotny          #+#    #+#             */
/*   Updated: 2020/07/30 10:32:29 by asolopov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	main(int argc, char **argv)
{
	t_asm		*core;
	t_operation	*list;

	if (argc == 2)
	{
		core = intialize_asm(argv[1]);
		list = NULL;
		read_file(core, core->source_fd, &list);
		write_champion(core, list);
		clear_t_asm((void *)core);
	}
	else
		ft_printf("./asm <filename.s>");
	return (0);
}
