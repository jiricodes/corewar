/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolopov <asolopov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 10:51:34 by jnovotny          #+#    #+#             */
/*   Updated: 2020/06/04 16:55:49 by asolopov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int main(int argc, char **argv)
{
	t_asm	*core;

	if (argc == 2)
	{
		core = intialize_asm(argv[1]);
		read_file(core, core->source_fd);
		ft_printf("{GREEN} SUCCESS {EOC}");
	}
	else
		ft_printf("./asm <filename.s>");
	return (0);
}