/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 22:48:23 by jnovotny          #+#    #+#             */
/*   Updated: 2019/10/19 19:00:01 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** strlcat() appends string src to the end of dst.
** It will append at most dstsize - strlen(dst) - 1 characters.
** It will then NUL-terminate, unless dstsize is 0 or the original dst string
** was longer than dstsize (in practice this should not happen as it means
** that either dstsize is incorrect or that dst is not a proper string).
*/

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t src_l;
	size_t dst_l;

	src_l = ft_strlen(src);
	dst_l = ft_strlen(dst);
	if (dst_l >= dstsize)
		return (dstsize + src_l);
	if (src_l < (dstsize - dst_l))
	{
		ft_memcpy(dst + dst_l, src, src_l);
		dst[dst_l + src_l] = '\0';
	}
	else
	{
		ft_memcpy(dst + dst_l, src, dstsize - dst_l - 1);
		dst[dstsize - 1] = '\0';
	}
	return (dst_l + src_l);
}
