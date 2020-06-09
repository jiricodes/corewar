/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 10:51:34 by jnovotny          #+#    #+#             */
/*   Updated: 2020/06/09 10:38:54 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int main(int argc, char **argv)
{
	t_asm	*core;

	if (argc == 2)
	{
		core = intialize_asm(argv[1]);
		ft_printf("{GREEN} Initialization done!{EOC}\n");
		read_file(core, core->source_fd);
		print_asmcore(core);
	}
	else
		ft_printf("./asm <filename.s>");
	return (0);
}