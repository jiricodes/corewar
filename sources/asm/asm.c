/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolopov <asolopov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 10:51:34 by jnovotny          #+#    #+#             */
/*   Updated: 2020/06/08 23:34:38 by asolopov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int main(int argc, char **argv)
{
	t_asm	*core;

	if (argc == 2)
	{
		core = intialize_asm(argv[1]);
		ft_printf("{GREEN} Initialization done!{EOC}");
		read_file(core, core->source_fd);
		print_asmcore(core);
	}
	else
		ft_printf("./asm <filename.s>");
	return (0);
}