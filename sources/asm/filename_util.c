/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filename_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 11:29:13 by jnovotny          #+#    #+#             */
/*   Updated: 2020/06/04 11:40:02 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** File name utility function, that checks whether given file is "*.s" type
** If true, returns ".cor" file name. Else returns NULL
*/

char	*filename_pars(const char *source, const char *src_type, const char *target_type)
{
	char	*target;
	size_t	l;

	target = NULL;
	l = ft_strlen(source);
	if (l > 2)
	{
		if (source[l - 2] == '.' && source[l - 1] == 's')
		{
			target = ft_strjoin(ft_strsub(source, 0, l - 2), ".cor")
		}
	}
}