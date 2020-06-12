/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 10:40:56 by jnovotny          #+#    #+#             */
/*   Updated: 2020/06/12 13:22:59 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static t_vm	*init_vm()
{
	t_vm	*core;

	core = (t_vm *)ft_memalloc(sizeof(t_vm));
	if (!core)
		ft_error_exit("Malloc at init_vm", NULL, NULL);
	return (core);
}

int main(int argc, char **argv)
{
	t_vm *core;

	if (argc == 2)
	{
		core = init_vm();
		core->champ = init_champ(argv[1]);
		ft_printf("Champ initialized\n");
		load_champ(core->champ);
		init_arena(core);
		insert_champ_to_arena(core->arena, core->champ, 64);
		show_arena(core);
	}
	return (0);
}