/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filename_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 11:29:13 by jnovotny          #+#    #+#             */
/*   Updated: 2020/06/04 12:37:52 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** File name utility function, that checks whether given file is "*.s" type
** If true, returns ".cor" file name. Else returns NULL
*/

char	*filename_pars(const char *source, const char *src_type,\
		const char *target_type)
{
	char	*target;
	char	*basename;

	target = NULL;
	if (ft_strendwith(source, src_type))
	{
		basename = ft_strsub(source, 0, ft_strlen(source) - ft_strlen(src_type));
		target = ft_strjoin(basename, target_type);
		free(basename);
	}
	return (target);
}