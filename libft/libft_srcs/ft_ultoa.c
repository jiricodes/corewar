/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 11:42:27 by jnovotny          #+#    #+#             */
/*   Updated: 2019/11/13 11:44:25 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static short	ft_ulonglen(unsigned long n)
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

char			*ft_ultoa(unsigned long n)
{
	char	*res;
	size_t	len;
	size_t	i;

	len = ft_ulonglen(n);
	if (!(res = ft_strnew(len)))
		return (NULL);
	i = 0;
	if (n == 0)
		res[i] = '0';
	while (n != 0)
	{
		res[len - 1] = (n % 10) + 48;
		n = n / 10;
		len = len - 1;
	}
	return (res);
}
