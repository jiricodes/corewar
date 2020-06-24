/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_maker.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakela <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 18:43:24 by jmakela           #+#    #+#             */
/*   Updated: 2020/06/24 13:09:20 by jmakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Strcpy function for sprintf.
** Normal strcpy except it copies size_t amount of characters.
*/

char		*pf_strcpy(char *dest, const char *src, size_t j)
{
	size_t i;

	i = 0;
	while (j > 0)
	{
		dest[i] = src[i];
		i = i + 1;
		j = j - 1;
	}
	if (i != 0)
		dest[i] = '\0';
	return (dest);
}

/*
** Strjoin function for printf.
** Normal strjoin, with the only exception that it gets
** the lengths of the strings as parameters. This is used
** isntead of ft_strlen, because sometimes null characters can
** be written in the middle of the string and in those cases
** the null characters should be printed. ft_strlen would
** give wrong values in those special cases.
*/

char		*pf_strjoin(char const *s1, char const *s2, int i, int j)
{
	char	*tmp;
	size_t	total;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	if (!(tmp = (char*)malloc(sizeof(char) * (i + j + 1))))
		exit(-1);
	total = i + j;
	while ((i + j) >= 0)
	{
		if (j >= 0)
		{
			tmp[i + j] = s2[j];
			j = j - 1;
		}
		else
		{
			tmp[i + j] = s1[i - 1];
			i = i - 1;
		}
	}
	tmp[total] = '\0';
	return (tmp);
}

/*
** Appends substring to the final string.
** Gets string pointer as parameter and len of how many
** chars from str should be joined to the final string.
** Makes a substring out of str and strjoins it to temp.
** Deletes final string and sets final string to be temp.
*/

t_printf	*append_substr(t_printf *pf, char *str, size_t len)
{
	char *sub;
	char *temp;

	pf->total = pf->total + len;
	if (!(sub = ft_strsub(str, 0, len)))
		exit(-1);
	if (!(temp = ft_strjoin(pf->final, sub)))
		exit(-1);
	ft_strdel(&pf->final);
	pf->final = temp;
	free(sub);
	return (pf);
}

/*
** Gets character c and int count to create and join a string.
** Allocates new string pointer and fills it with character c.
** Strjoins it with final string to temp, deletes final string
** and sets final string to be temp.
*/

t_printf	*str_maker(t_printf *pf, char c, int count)
{
	int		i;
	char	*str;
	char	*temp;

	i = 0;
	if (count > 0)
	{
		if (!(str = (char*)malloc(sizeof(char) * (count + 1))))
			exit(-1);
		while (i < count)
		{
			str[i] = c;
			i = i + 1;
		}
		str[i] = '\0';
		if (!(temp = pf_strjoin(pf->final, str, pf->total, count)))
			exit(-1);
		ft_strdel(&pf->final);
		pf->final = temp;
		free(str);
		pf->total = pf->total + count;
	}
	return (pf);
}
