/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_args_flags.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 08:09:51 by jnovotny          #+#    #+#             */
/*   Updated: 2020/07/28 08:18:07 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int	handle_pt2(t_vm *core, char **argv, int argc, int i)
{
	if (ft_strequ(argv[i], "-log") && i < argc - 1 &&\
		ft_strlen(argv[i + 1]) == 1 && ft_strchr(F_LOG_STR, argv[i + 1][0]))
	{
		core->flags->log = argv[i + 1][0] - 48;
		return (1);
	}
	else if (ft_strequ(argv[i], "-a"))
		core->flags->aff = 1;
	else if (ft_strequ(argv[i], "-s"))
		core->flags->silent = 1;
	else
		process_player(core, NULL, argv[i]);
	return (0);
}

int			handle_flags(t_vm *core, char **argv, int argc, int i)
{
	if (ft_strequ(argv[i], "-dump") || ft_strequ(argv[i], "-d"))
	{
		process_dump(core, i < argc - 1 ? argv[i + 1] : "0", argv[i]);
		return (1);
	}
	else if (ft_strequ(argv[i], "-v"))
	{
		core->flags->vfx = 1;
		core->flags->silent = 1;
	}
	else if (ft_strequ(argv[i], "-n"))
	{
		if (i < argc - 2)
			process_player(core, argv[i + 1], argv[i + 2]);
		else
			vm_error("Player manual numbering error", core->flags->log);
		return (2);
	}
	else
		return (handle_pt2(core, argv, argc, i));
	return (0);
}
