/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 22:48:42 by jnovotny          #+#    #+#             */
/*   Updated: 2019/10/19 16:26:33 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	size_t origin;
	size_t i;

	i = 0;
	origin = ft_strlen(s1);
	while (i < n && s2[i] != '\0')
	{
		s1[origin + i] = s2[i];
		i = i + 1;
	}
	s1[origin + i] = '\0';
	return (s1);
}
