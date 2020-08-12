/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_bytecode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolopov <asolopov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 12:05:11 by asolopov          #+#    #+#             */
/*   Updated: 2020/08/12 20:58:30 by asolopov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	write_champion(t_asm *core, t_operation *op)
{
	core->core_fd = open(core->target_file, O_RDWR | O_TRUNC | O_CREAT, 0600);
	if (core->core_fd < 0)
		ft_error_exit("Open Error on target file", (void *)core, clear_t_asm);
	write_headers(core);
	write_exec_code(core, op);
	ft_printf("Writing output program to: %s\n", core->target_file);
}
