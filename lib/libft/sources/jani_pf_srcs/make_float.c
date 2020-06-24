/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_float.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakela <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 18:24:58 by jmakela           #+#    #+#             */
/*   Updated: 2020/06/24 13:09:04 by jmakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Rounds up the string.
** Checks if amount of precision position in the string
** has a number, which is higher than 5 and previous number
** is less than 9. If this is the case, increase the previous
** number by one, since this is the last number to be printed.
** In the case of 9 we loop backwards until we find a number
** that is not 9 and increase that by one. As we find 9's we
** assign them to be 0, because we round up every value until
** not 9. If We find that index is at the 0 position (which
** is the decimal point) we should then round up the whole
** number part, in that case we check if the number >= 0 or
** number < 0 and either increase or decrease the value.
*/

static t_printf	*roundup(t_printf *pf)
{
	int i;

	i = pf->precision;
	if (i > 99)
		i = 99;
	if ((pf->rounded[i] > 52) && i == 1)
		i = i - 1;
	else if ((pf->rounded[i] > 52) && (pf->rounded[i - 1] < 57) && i > 1)
		pf->rounded[i - 1] = pf->rounded[i - 1] + 1;
	else if ((pf->rounded[i] > 52) && (pf->rounded[i - 1] == 57))
	{
		i = i - 1;
		while ((pf->rounded[i] == 57) && (i > 0))
		{
			pf->rounded[i] = 48;
			i = i - 1;
		}
		if (i > 0)
			pf->rounded[i] = pf->rounded[i] + 1;
	}
	if (i == 0 && pf->nbr >= 0)
		pf->nbr = pf->nbr + 1;
	else if (i == 0 && pf->nbr < 0)
		pf->nbr = pf->nbr - 1;
	return (pf);
}

/*
** Gets the whole and rounded up fraction of double.
** Allocates space enough to deal with first 100 digits
** of precision, this is overkill since printf only provides
** around 50 numbers of precision for doubles.
**
** First assign double value into int, so we cab take the integer part.
** Then assign the double value into another double as an integer.
** Remove from the first double the int assigned double and we are left
** with just the fraction. We do *10 to the double to move the first
** digit of the fraction to the integer part.
** Assign the double value into string[i] position, this assign only
** the integer part. Keep repeating the operation to get desired amount
** of fractions into a string, After that, we round up the string.
*/

t_printf		*get_parts(t_printf *pf)
{
	long double	whole;
	long double temp;
	int			i;

	i = 1;
	(!(pf->rounded = (char*)malloc(sizeof(char) * 101))) ? exit(-1) : 0;
	whole = (int)pf->f_nbr;
	pf->rounded[0] = '.';
	temp = pf->f_nbr;
	while (i < 100)
	{
		temp = temp - whole;
		temp = temp * 10;
		whole = (int)temp;
		pf->rounded[i] = whole + 48;
		i = i + 1;
	}
	pf->rounded[i] = '\0';
	roundup(pf);
	pf->whole = convert(pf);
	return (pf);
}
