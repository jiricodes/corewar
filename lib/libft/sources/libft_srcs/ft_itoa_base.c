/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 15:36:22 by jnovotny          #+#    #+#             */
/*   Updated: 2019/11/13 11:38:25 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa_base(int value, int base, int upcase)
{
	char	*str;
	long	len;

	if (base > 16 || base < 2 || (base != 0 && value < 0))
		return (NULL);
	if (base == 10)
		return (ft_itoa(value));
	len = ft_base_len(value, base);
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
