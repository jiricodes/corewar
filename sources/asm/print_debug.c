/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 21:23:59 by jnovotny          #+#    #+#             */
/*   Updated: 2020/06/08 21:28:28 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	print_asmcore(t_asm *core)
{
	ft_printf("{U}ASM Core{EOC}\n");
	ft_printf("Source FD: %d\n", core->source_fd);
	ft_printf("Target FD: %d\n", core->core_fd);
	ft_printf("Champ's Name: %s\n", core->champ_name);
	ft_printf("Champ's Comment: %s\n", core->champ_comment);
}