/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 17:15:39 by jnovotny          #+#    #+#             */
/*   Updated: 2019/10/21 13:24:45 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Allocates (with malloc(3)) and returns a copy of the string given
** as argument without whitespaces at the beginning or at
** the end of the string. Will be considered as whitespaces the
** following characters ’ ’, ’\n’ and ’\t’. If s has no whitespaces
** at the beginning or at the end, the function returns a
** copy of s. If the allocation fails the function returns NULL.
*/

char	*ft_strtrim(char const *s)
{
	size_t	end;
	size_t	start;
	char	*res;

	if (!s)
		return (NULL);
	end = ft_strlen(s) - 1;
	start = 0;
	while (s[start] == ' ' || s[start] == '\n' || s[start] == '\t')
		start = start + 1;
	while ((s[end] == ' ' || s[end] == '\n' || s[end] == '\t') && (end != 0))
		end = end - 1;
	if (end < start)
		return ("");
	res = ft_strnew(end - start + 2);
	if (res == NULL)
		return (NULL);
	res = ft_strsub(s, start, end - start + 1);
	return (res);
}
