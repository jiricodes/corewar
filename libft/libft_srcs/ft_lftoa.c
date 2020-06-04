/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lftoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 17:22:55 by jnovotny          #+#    #+#             */
/*   Updated: 2019/11/18 15:48:46 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Long float itoa with decimal precision
*/

long	ft_front_adj(long double n, unsigned int precision, char *back)
{
	long nb;

	if (n >= 0)
		nb = (precision == 0 || precision < ft_strlen(back)) ? \
			(long)(n + 0.5) : (long)n;
	else
		nb = (precision == 0 || precision < ft_strlen(back)) ? \
			(long)(n - 0.5) : (long)n;
	return (nb);
}

char	*ft_double_backcheck(char *back, unsigned int precision)
{
	size_t	s_len;
	char	*tmp;
	char	*res;

	s_len = ft_strlen(back);
	if (precision > s_len)
	{
		tmp = ft_strnew(precision - s_len);
		ft_memset((void*)tmp, 48, precision - s_len);
		res = ft_strjoin(tmp, back);
		free(tmp);
		free(back);
		return (res);
	}
	else if (precision < s_len)
	{
		if (back[0] == '1')
			back[0] = '0';
		if (s_len > 1)
			back[s_len - 1] = '\0';
	}
	return (back);
}

char	*ft_glue_double(char *front, char *back, unsigned int precision)
{
	char *tmp;
	char *res;

	back = ft_double_backcheck(back, precision);
	if (precision != 0)
	{
		tmp = ft_strjoin(front, ".");
		res = ft_strjoin(tmp, back);
		free(tmp);
	}
	else
		res = ft_strjoin(front, ".");
	free(front);
	if (back)
		free(back);
	return (res);
}

char	*ft_front_double(long double n, long nb)
{
	char	*res;

	if (nb == 0 && n < 0)
		res = ft_strdup("-0");
	else
		res = ft_ltoa(nb);
	return (res);
}

char	*ft_lftoa(long double n, unsigned int precision)
{
	char			*front;
	char			*back;
	long double		dec;
	long			nb;
	unsigned int	prec;

	prec = precision;
	nb = (long)n;
	dec = n - nb;
	while (prec-- > 0)
		dec = dec * 10;
	dec += dec > 0 ? 0.5 : -0.5;
	nb = (long)dec;
	back = ft_ultoa(nb < 0 ? -1 * nb : nb);
	nb = ft_front_adj(n, precision, back);
	front = ft_front_double(n, nb);
	return (ft_glue_double(front, back, precision));
}
