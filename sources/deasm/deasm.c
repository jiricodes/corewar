/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deasm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolopov <asolopov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 12:42:40 by asolopov          #+#    #+#             */
/*   Updated: 2020/08/12 21:01:03 by asolopov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "deasm.h"

int		main(int argc, char **argv)
{
	t_deasm *core;

	if (argc == 2)
	{
		core = initialize_deasm(argv[1]);
		read_file(core, core->source_fd);
		core->target_fd = open(core->target_file,\
				O_RDWR | O_TRUNC | O_CREAT, 0600);
		if (core->target_fd < 0)
			ft_error_exit("Couldn't open target", (void *)core, clear_t_deasm);
		decode_exec(core, core->raw_code);
		clear_t_deasm(core);
	}
	else
		ft_printf("./deasm <filename.cor>");
	return (0);
}
