/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 14:23:32 by jnovotny          #+#    #+#             */
/*   Updated: 2019/10/21 12:46:10 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** The memcmp() function compares byte string s1 against byte string s2.
** Both strings are assumed to be n bytes long.
** The memcmp() function returns zero if the two strings are identical,
** otherwise returns the difference between the first two differing bytes.
*/

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t i;

	i = 0;
	if (s1 == s2 || n == 0)
		return (0);
	while (i < n)
	{
		if (((unsigned const char*)s1)[i] != ((unsigned const char*)s2)[i])
		{
			return (((unsigned const char*)s1)[i] - \
				((unsigned const char*)s2)[i]);
		}
		i = i + 1;
	}
	return (0);
}
