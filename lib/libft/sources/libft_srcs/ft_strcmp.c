/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 12:32:10 by jnovotny          #+#    #+#             */
/*   Updated: 2019/10/19 17:51:22 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** The strcmp() and strncmp() functions lexicographically compare
** the null-terminated strings s1 and s2.
** The strncmp() function compares not more than n characters.
** Because strncmp() is designed for comparing strings rather than binary data,
** characters that appear after a `\0' character are not compared.
*/

int		ft_strcmp(const char *s1, const char *s2)
{
	if (ft_strlen(s1) >= ft_strlen(s2))
		return (ft_memcmp(s1, s2, ft_strlen(s1)));
	else
		return (ft_memcmp(s1, s2, ft_strlen(s2)));
}
