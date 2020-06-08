/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 17:46:11 by jnovotny          #+#    #+#             */
/*   Updated: 2020/02/24 11:39:14 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Allocates (with malloc(3)) and returns an array of “fresh”
** strings (all ending with ’\0’, including the array itself) obtained
** by spliting s using the character c as a delimiter.
** If the allocation fails the function returns NULL. Example:
** ft_strsplit("*hello*fellow***students*", ’*’)
** returns the array ["hello", "fellow", "students"].
*/

size_t	ft_wrdcnt(char const *s, char c)
{
	size_t i;
	size_t cnt;

	i = 0;
	cnt = 0;
	if (s[i] == '\0')
		return (cnt);
	if (s[i] != c)
		cnt = cnt + 1;
	i++;
	while (s[i] != '\0')
	{
		if ((s[i] != c) && (s[i - 1] == c))
			cnt = cnt + 1;
		i = i + 1;
	}
	return (cnt);
}

char	**ft_strsplit(char const *s, char c)
{
	char	**res;
	size_t	i;
	size_t	wrd_l;
	size_t	wrd_i;

	if (!s)
		return (NULL);
	if (!(res = (char**)malloc(sizeof(char*) * (ft_wrdcnt(s, c) + 1))))
		return (NULL);
	i = 0;
	wrd_i = 0;
	while (s[i] != '\0' && wrd_i < ft_wrdcnt(s, c))
	{
		wrd_l = 0;
		while (s[i] == c)
			i = i + 1;
		while ((s[i + wrd_l] != c) && (s[i + wrd_l] != '\0'))
			wrd_l = wrd_l + 1;
		if (s[i] != '\0')
			res[wrd_i] = ft_strsub(s, i, wrd_l);
		i = i + wrd_l;
		wrd_i = wrd_i + 1;
	}
	res[wrd_i] = NULL;
	return (res);
}
