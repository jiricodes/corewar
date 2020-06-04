/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 23:59:57 by jnovotny          #+#    #+#             */
/*   Updated: 2019/10/21 14:28:37 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*res;
	size_t	i;

	i = 0;
	if (s == NULL || f == NULL)
		return (NULL);
	if (!(res = ft_strnew(ft_strlen(s))))
		return (NULL);
	while (s[i] != '\0')
	{
		res[i] = f(i, s[i]);
		i = i + 1;
	}
	return (res);
}
