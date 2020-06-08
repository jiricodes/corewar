/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 08:21:44 by jnovotny          #+#    #+#             */
/*   Updated: 2019/10/21 14:31:57 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char *sub;

	if (!s)
		return (NULL);
	sub = ft_memalloc(len + 1);
	if (sub == NULL)
		return (NULL);
	sub = ft_memcpy(sub, s + start, len);
	return (sub);
}
