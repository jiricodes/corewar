/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 12:48:57 by jnovotny          #+#    #+#             */
/*   Updated: 2020/06/04 12:19:04 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Lexicographical comparison between s1 and s2. If the 2
** strings are identical the function returns 1, or 0 otherwise.
*/

int		ft_strequ(char const *s1, char const *s2)
{
	while (s1[0] != '\0' && !(*(s1) ^ *(s2)))
	{
		s1++;
		s2++;
	}
	return (!(*(s1) ^ *(s2)));
}
