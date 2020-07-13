/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 21:23:59 by jnovotny          #+#    #+#             */
/*   Updated: 2020/07/13 12:14:29 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	print_asmcore(t_asm *core)
{
	ft_printf("%{UNDERLINE}ASM Core%{EOC}\n");
	ft_printf("Source FD: %d\n", core->source_fd);
	ft_printf("Target FD: %d\n", core->core_fd);
	ft_printf("Champ's Name: %s\n", core->champ_name);
	ft_printf("Champ's Comment: %s\n", core->champ_comment);
}
