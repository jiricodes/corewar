/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakela <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 16:00:27 by jmakela           #+#    #+#             */
/*   Updated: 2020/07/23 16:00:29 by jmakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** finds first occurrence of c in str
** so basically strchr, but returns -1 instead of null
** made it easier for me to check positions
*/

int				ft_chrpos(char *str, char c)
{
	int i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i = i + 1;
	}
	return (-1);
}

/*
** determines if argum string is hex
** each char has to be part of hexmask string
** else not hex
*/

int				is_hex(char *argum)
{
	int		i;
	char	*hexmask;

	hexmask = "0123456789abcdefABCDEF";
	if (argum[0] == DIRECT_CHAR)
		i = 3;
	else
		i = 2;
	if (argum[i - 2] == '0' && (argum[i - 1] == 'x' || argum[i - 1] == 'X'))
	{
		while (argum[i] != '\0')
		{
			if (ft_chrpos(hexmask, argum[i]) < 0)
				return (0);
			i = i + 1;
		}
		return (1);
	}
	return (0);
}

/*
** rises number to the power
** it is being used to convert hex to decimal
*/

unsigned long	ft_pow(int number, int power)
{
	unsigned long total;

	total = number;
	if (!power)
		return (1);
	else if (power == 1)
		return (number);
	else
	{
		while (power > 1)
		{
			total = total * number;
			power = power - 1;
		}
	}
	return (total);
}

/*
** converts hex to decimal.
*/

static void		argum_len(char *argum, int *len, int *i)
{
	if (argum[0] == DIRECT_CHAR)
	{
		*len = ft_strlen(argum) - 4;
		*i = 3;
	}
	else
	{
		*len = ft_strlen(argum) - 3;
		*i = 2;
	}
}

char			*x_to_deci(char *argum)
{
	unsigned long	hex;
	int				len;
	int				val;
	int				i;

	hex = 0;
	val = 0;
	argum_len(argum, &len, &i);
	while (argum[i] != '\0')
	{
		if (argum[i] >= '0' && argum[i] <= '9')
			val = argum[i] - 48;
		else if (argum[i] >= 'a' && argum[i] <= 'f')
			val = argum[i] - 97 + 10;
		else if (argum[i] >= 'A' && argum[i] <= 'F')
			val = argum[i] - 65 + 10;
		hex = hex + (val * ft_pow(16, len));
		len = len - 1;
		i = i + 1;
	}
	return (ft_ultoa(hex));
}
