/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 22:47:45 by jnovotny          #+#    #+#             */
/*   Updated: 2019/10/17 22:47:45 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *s1, const char *s2)
{
	size_t origin;

	origin = ft_strlen(s1);
	ft_memcpy(s1 + origin, s2, ft_strlen(s2) + 1);
	return (s1);
}
