/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolopov <asolopov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 10:51:34 by jnovotny          #+#    #+#             */
/*   Updated: 2020/07/01 12:38:56 by asolopov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

//Maybe we'll move the t_operation pointer inside t_asm pointer at some point?
int main(int argc, char **argv)
{
	t_asm		*core;
	t_operation	*list;
	t_operation *cpy;

	if (argc == 2)
	{
		core = intialize_asm(argv[1]);
		list = NULL;
		ft_printf("%{GREEN}Initialization done!%{EOC}\n");
		read_file(core, core->source_fd, &list);
		// print_asmcore(core);
		//moved print here to error check
		// print_list(list);
		ft_printf("Total size in bytes: %d\n", core->byte_size);
		cpy = list;
		while (cpy)
		{
			check_operation(cpy, list);
			cpy = cpy->next;
		}
		write_champion(core, list);
		// clear_t_asm((void *)core);
	}
	else
		ft_printf("./asm <filename.s>");
	// while(1);
	return (0);
}