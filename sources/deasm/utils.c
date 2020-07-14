/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolopov <asolopov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 16:16:18 by asolopov          #+#    #+#             */
/*   Updated: 2020/07/14 12:56:41 by asolopov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "deasm.h"

int32_t	decode(const uint8_t *source, size_t size)
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

int		decode_arg(t_operation *op, int cnt, int8_t *rawcode, int move)
{
	int jump;

	if (op->argtypes[cnt] == T_REG_CODE)
	{
		jump = 1;
		op->arg[cnt] = ft_itoa(decode((uint8_t *)(rawcode + move), jump));
	}
	else if (op->argtypes[cnt] == T_DIR_CODE)
	{
		jump = op->t_dir_size;
		op->arg[cnt] = ft_itoa(decode((uint8_t *)(rawcode + move), jump));
	}
	else if (op->argtypes[cnt] == T_IND_CODE)
	{
		jump = 2;
		op->arg[cnt] = ft_itoa(decode((uint8_t *)(rawcode + move), jump));
	}
	return (jump);
}
