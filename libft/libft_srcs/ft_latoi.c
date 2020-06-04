/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_latoi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 22:44:01 by jnovotny          #+#    #+#             */
/*   Updated: 2020/01/21 13:20:03 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long		ft_latoi(const char *str)
{
	size_t			i;
	long long int	sign;
	long long int	rslt;

	i = 0;
	sign = 1;
	rslt = 0;
	while (ft_isspace(str[i]))
		i = i + 1;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '+' || str[i] == '-')
		i = i + 1;
	while (ft_isdigit(str[i]))
	{
		if ((rslt >= 922337203685477580) && (str[i] - '0') > 7)
			return ((sign == 1) ? -1 : 0);
		rslt = rslt * 10 + (long long int)(str[i] - 48);
		i = i + 1;
	}
	return (sign * rslt);
}
