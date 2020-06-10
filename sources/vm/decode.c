/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decode.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 10:47:50 by jnovotny          #+#    #+#             */
/*   Updated: 2020/06/10 10:50:01 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int32_t		decode(const uint8_t *source, size_t size)
{
	int32_t result;
	uint8_t sign;
	size_t i;

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

