/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 22:46:14 by jnovotny          #+#    #+#             */
/*   Updated: 2019/10/21 12:04:36 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t i;

	i = 0;
	if (dst == src || !n)
		return (dst);
	while (i < n)
	{
		((unsigned char*)dst)[i] = ((unsigned char*)src)[i];
		i = i + 1;
	}
	return (dst);
}
