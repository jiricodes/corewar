/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolopov <asolopov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 16:16:18 by asolopov          #+#    #+#             */
/*   Updated: 2020/07/13 16:17:04 by asolopov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "deasm.h"

int32_t		decode(const uint8_t *source, size_t size)
{
	int32_t	result;
	uint8_t	sign;
	size_t	i;

	if (source[0] & 128)
		sign = 255;
	else
		sign = 0;
	result = 0;
	i = 0;
	while (i < size)
	{
		result += (source[size - (i + 1)] ^ sign) << (i * 8);
		i++;
	}
	if (sign)
		result = ~result;
	return (result);
}

char	*filename_pars(const char *source, const char *src_type,\
		const char *target_type)
{
	char	*target;
	char	*base;

	target = NULL;
	if (ft_strendwith(source, src_type))
	{
		base = ft_strsub(source, 0, ft_strlen(source) - ft_strlen(src_type));
		target = ft_strjoin(base, target_type);
		free(base);
	}
	return (target);
}

void	clear_t_deasm(void *object)
{
	free(object);
}
