/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 11:48:04 by jnovotny          #+#    #+#             */
/*   Updated: 2020/06/10 13:50:18 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	print_champ_header(t_champ *champ)
{
	ft_printf("Magic: %#x\n", champ->header->magic);
	ft_printf("Name: %s\n", champ->header->prog_name);
	ft_printf("Champ weight: %d\n", champ->header->prog_size);
	ft_printf("Comment: %s\n", champ->header->comment);
}