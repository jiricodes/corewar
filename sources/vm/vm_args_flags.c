/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_args_flags.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 08:09:51 by jnovotny          #+#    #+#             */
/*   Updated: 2020/08/04 17:40:04 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int	handle_pt2(t_vm *core, char **argv, int argc, int i)
{
	if (ft_strequ(argv[i], "-log"))
	{
		if (i < argc - 1 && ft_isnumber(argv[i + 1]))
		{
			core->flags->log = ft_atoi(argv[i + 1]);
			return (1);
		}
		else
			vm_error("Incorrect usage of -log flag");
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
			vm_error("Player manual numbering error");
		return (2);
	}
	else
		return (handle_pt2(core, argv, argc, i));
	return (0);
}
