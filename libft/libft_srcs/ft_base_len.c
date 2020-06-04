/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_base_len.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 16:06:22 by jnovotny          #+#    #+#             */
/*   Updated: 2019/11/14 16:50:48 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_base_len(long nb, long base)
{
	long	len;

	len = 1;
	while (ft_power_l(base, len) <= nb)
		len++;
	return (len);
}

size_t	ft_base_ulen(unsigned long nb, long base)
{
	size_t	len;

	len = 1;
	while (ft_power_ul(base, len) <= nb)
		len++;
	return (len);
}
