/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 22:48:51 by jnovotny          #+#    #+#             */
/*   Updated: 2019/10/19 17:28:14 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t l;

	l = ft_strlen(src);
	if (l >= len)
		ft_memcpy(dst, src, len);
	else
	{
		ft_memcpy(dst, src, len);
		while (l < len)
		{
			dst[l] = '\0';
			l = l + 1;
		}
	}
	return (dst);
}
