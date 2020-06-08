/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 11:51:22 by jnovotny          #+#    #+#             */
/*   Updated: 2019/11/15 17:54:52 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_ultoa_base(unsigned long value, int base, int upcase)
{
	char	*str;
	size_t	len;

	if (base > 16 || base < 2)
		return (NULL);
	if (base == 10)
		return (ft_ltoa(value));
	if (((long)value >= LONG_MAX / base || value >= ULONG_MAX / base)\
		&& base == 16)
		len = 16;
	else
		len = ft_base_ulen(value, base);
	str = ft_strnew(len);
	str[len] = '\0';
	while (len-- > 0)
	{
		if (base > 10 && (value % base >= 10) && upcase)
			str[len] = (value % base) + 55;
		else if (base > 10 && (value % base >= 10))
			str[len] = (value % base) + 87;
		else
			str[len] = (value % base) + 48;
		value = value / base;
	}
	return (str);
}
