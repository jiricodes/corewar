/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 13:40:26 by jnovotny          #+#    #+#             */
/*   Updated: 2019/10/21 13:43:00 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Checks whether given character is a white space
*/

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\r' || c == '\n' || \
		c == '\f' || c == '\v' || c == '\t')
		return (1);
	return (0);
}
