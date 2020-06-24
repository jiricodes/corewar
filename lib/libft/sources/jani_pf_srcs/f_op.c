/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_op.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakela <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 18:14:16 by jmakela           #+#    #+#             */
/*   Updated: 2020/06/24 13:08:55 by jmakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Left alings double for saving.
** First checks if space should be saved,
** then negativity, then plus, then saves
** the whole part of the number and precision
** amount of rounded up fraction of the number.
** Finally saves width amount of spaces to
** the final string.
*/

static t_printf	*left_align_f(t_printf *pf)
{
	if (!(pf->neg) && !(pf->plus) && pf->space)
		str_maker(pf, ' ', 1);
	else if (pf->neg)
		str_maker(pf, '-', 1);
	else if (pf->plus)
		str_maker(pf, '+', 1);
	append_substr(pf, pf->whole, ft_strlen(pf->whole));
	append_substr(pf, pf->rounded, pf->precision);
	if (pf->width)
		str_maker(pf, ' ', pf->width);
	return (pf);
}

/*
** Right aligns double for saving.
** First checks if space should be written, then
** if number was negative and there is width with
** zero flag, else if the number was not negative and
** there is plus and width with zero flag. Saves width
** amount of zeroes of spaces depending on zero flag,
** if there was no zero flag, saves the negativity and
** plus. Finally saves the whole part and precision
** amount of rounded fraction to the final string.
*/

static t_printf	*right_align_f(t_printf *pf)
{
	if ((!(pf->neg) && !(pf->plus) && pf->space) &&
		(!(pf->width) || (pf->width && pf->zero)))
		str_maker(pf, ' ', 1);
	if (pf->neg && pf->width && pf->zero)
	{
		str_maker(pf, '-', 1);
		pf->neg = 0;
		pf->plus = 0;
	}
	else if (!(pf->neg) && pf->plus && pf->width && pf->zero)
	{
		str_maker(pf, '+', 1);
		pf->plus = 0;
	}
	if (pf->width)
		(pf->zero) ? (str_maker(pf, '0', pf->width)) :
		(str_maker(pf, ' ', pf->width));
	if (pf->neg)
		str_maker(pf, '-', 1);
	else if (!(pf->neg) && pf->plus)
		str_maker(pf, '+', 1);
	append_substr(pf, pf->whole, ft_strlen(pf->whole));
	append_substr(pf, pf->rounded, pf->precision);
	return (pf);
}

/*
** Finds out correct width and precision.
** Takes integer copy of the double value and checks
** for negativity. Assigns precision if there isn't one,
** since 6 decimals is what printf prints without specifying
** precision. Calls get_parts make create strings out of whole
** and fraction parts of the number. Based on the strlen of
** whole, we find out correct width and call proper alignment
** function based on  minus flag.
*/

static t_printf	*f_handler(t_printf *pf)
{
	pf->nbr = pf->f_nbr;
	if (pf->f_nbr < 0)
	{
		pf->f_nbr = pf->f_nbr * -1;
		pf->neg = 1;
	}
	pf->precision = pf->precision + 1;
	if (pf->prec_true == 0)
		pf->precision = 7;
	if (pf->prec_true && pf->precision == 0 && pf->hash)
		pf->precision = 1;
	get_parts(pf);
	if (pf->precision == 1 && !pf->hash)
		pf->precision = 0;
	(pf->neg || pf->plus || (pf->minus && pf->space)
	|| (pf->zero && pf->space)) ?
	(pf->width = pf->width - ft_strlen(pf->whole) - pf->precision - 1) :
	(pf->width = pf->width - ft_strlen(pf->whole) - pf->precision);
	if (pf->width < 0)
		pf->width = 0;
	(pf->minus) ? (left_align_f(pf)) : (right_align_f(pf));
	free(pf->rounded);
	free(pf->whole);
	return (pf);
}

/*
** Gets double value from variable argument list.
** Checks for asterisk first, then gets the correct
** value from variable argument list based on type and
** length specifier. Sets base to 10 and calls f_handler
** to find out correct width and precision.
*/

t_printf		*float_op(t_printf *pf)
{
	if (pf->p_aste || pf->w_aste)
		get_asterisk(pf);
	if (pf->length[0] != '\0' && pf->length[0] != 'L')
	{
		write(2, "\033[31merror:\033[0m unsupported length option.\n", 43);
		exit(-1);
	}
	(ft_strcmp(pf->length, "L") == 0) ?
	(pf->f_nbr = (long double)va_arg(pf->args, long double)) :
	(pf->f_nbr = (double)va_arg(pf->args, double));
	pf->base = 10;
	f_handler(pf);
	return (pf);
}
