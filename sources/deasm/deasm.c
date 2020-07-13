/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deasm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolopov <asolopov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 12:42:40 by asolopov          #+#    #+#             */
/*   Updated: 2020/07/13 18:49:07 by asolopov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "deasm.h"

t_deasm	*initialize_deasm(char *filename)
{
	t_deasm	*core;
	char	*target_file;

	core = (t_deasm *)ft_memalloc(sizeof(t_deasm));
	if (!core)
		ft_error_exit("DeAsm malloc error", 0, 0);
	target_file = filename_pars(filename, SRC_TYPE, TRGT_TYPE);
	if (!target_file)
		ft_error_exit("Incorrect file type", (void *)core, clear_t_deasm);
	core->source_fd = open(filename, O_RDONLY);
	if (core->source_fd < 0)
		ft_error_exit("Couldn't open source", (void *)core, clear_t_deasm);
	core->target_fd = open(target_file, O_RDWR | O_CREAT, 0600);
	if (core->target_fd < 0)
		ft_error_exit("Couldn't open target", (void *)core, clear_t_deasm);
	return (core);
}

int	main(int argc, char **argv)
{
	t_deasm *core;

	if (argc == 2)
	{
		core = initialize_deasm(argv[1]);
		ft_printf("%{GREEN}Initialization done!%{EOC}\n");
		read_file(core, core->source_fd);
		decode_exec_code(core, core->raw_code);
	}
	else
		ft_printf("./deasm <filename.cor>");
}
