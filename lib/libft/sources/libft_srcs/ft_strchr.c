/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 22:47:52 by jnovotny          #+#    #+#             */
/*   Updated: 2019/10/19 16:27:35 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** The strchr() function locates the first occurrence of c
** (converted to a char) in the string pointed to by s.
** The terminating null character is considered to be part of the string;
** therefore if c is `\0', the functions locate the terminating `\0'.
**
** The strrchr() function is identical to strchr(),
** except it locates the last occurrence of c.
*/

char	*ft_strchr(const char *s, int c)
{
	return ((char*)ft_memchr(s, c, ft_strlen(s) + 1));
}
