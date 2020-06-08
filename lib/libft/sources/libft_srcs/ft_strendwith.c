/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strendwith.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 12:16:33 by jnovotny          #+#    #+#             */
/*   Updated: 2020/06/04 12:23:17 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Check whether given string src ends with the suffix
*/

int		ft_strendwith(const char *src, const char *suffix)
{
	size_t src_l;
	size_t suf_l;

	src_l = ft_strlen(src);
	suf_l = ft_strlen(suffix);
	return (suf_l <= src_l && ft_strequ(src + src_l - suf_l, suffix));
}
