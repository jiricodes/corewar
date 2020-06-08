/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_min_sqrt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 12:12:18 by jnovotny          #+#    #+#             */
/*   Updated: 2019/11/03 13:16:58 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Returns the minimum int square root x of given nb where x * x >= nb.
*/

int	ft_min_sqrt(int nb)
{
	int i;

	if (nb == 0 || nb == 1)
		return (nb);
	if (nb > 1)
	{
		i = 1;
		while (i < nb)
		{
			if ((i * i) >= nb)
				return (i);
			i = i + 1;
		}
	}
	return (0);
}
