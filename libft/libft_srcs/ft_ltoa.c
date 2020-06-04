/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 11:16:02 by jnovotny          #+#    #+#             */
/*   Updated: 2019/11/13 11:42:05 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Allocate (with malloc(3)) and returns a “fresh” string ending with ’\0’
** representing the long n given as argument.
** Negative numbers must be supported. If the allocation fails,
** the function returns NULL.
*/

static short	ft_longlen(long n)
{
	size_t cnt;

	cnt = (n <= 0 ? 1 : 0);
	while (n != 0)
	{
		n = n / 10;
		cnt = cnt + 1;
	}
	return (cnt);
}

char			*ft_ltoa(long n)
{
	char	*res;
	size_t	len;
	size_t	i;
	short	sign;

	len = ft_longlen(n);
	if (!(res = ft_strnew(len)))
		return (NULL);
	i = 0;
	sign = 1;
	if (n == 0)
		res[i] = '0';
	if (n < 0)
	{
		res[i] = '-';
		sign = -1;
	}
	while (n != 0)
	{
		res[len - 1] = (sign * (n % 10)) + 48;
		n = n / 10;
		len = len - 1;
	}
	return (res);
}
