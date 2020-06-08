/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 13:05:49 by jnovotny          #+#    #+#             */
/*   Updated: 2019/10/19 13:18:49 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** The memmove() function copies len bytes from string src to string dst.
** The two strings may overlap;
** the copy is always done in a non-destructive manner.
*/

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	if (src < dst && src + len > dst)
	{
		while (len > 0)
		{
			len = len - 1;
			((unsigned char*)dst)[len] = ((unsigned char*)src)[len];
		}
	}
	else
	{
		ft_memcpy(dst, src, len);
	}
	return (dst);
}
