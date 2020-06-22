/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 11:48:04 by jnovotny          #+#    #+#             */
/*   Updated: 2020/06/12 12:24:48 by jnovotny         ###   ########.fr       */
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

void	print_code(t_champ *champ)
{
	size_t i;

	i = 0;
	while (i < champ->header->prog_size)
	{
		ft_printf("%02x\n", champ->raw[i]);
		i++;
	}
}