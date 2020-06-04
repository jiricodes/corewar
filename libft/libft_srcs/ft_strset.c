/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 09:51:50 by jnovotny          #+#    #+#             */
/*   Updated: 2019/11/13 10:13:32 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Sets n characters to char c
*/

void	ft_strset(char *str, char c, size_t n)
{
	size_t i;

	i = 0;
	while (i < n)
	{
		str[i] = c;
		i++;
	}
}
