/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   di_op.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakela <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 18:06:17 by jmakela           #+#    #+#             */
/*   Updated: 2020/06/24 13:28:23 by jmakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Left aligns the integer and saves it to the final string.
** First checks for space flag, then negativity and plus.
** Saves precision amount of zeroes, the integer string
** and finally width amount of ' ' to the final string.
*/

static t_printf	*left_align_int(t_printf *pf, char *str_nbr)
{
	if (!(pf->neg) && !(pf->plus) && pf->space)
		str_maker(pf, ' ', 1);
	else if (pf->neg)
		str_maker(pf, '-', 1);
	else if (pf->plus)
		str_maker(pf, '+', 1);
	if (pf->precision)
		str_maker(pf, '0', pf->precision);
	if (pf->nbrlen != 0)
		append_substr(pf, str_nbr, pf->nbrlen);
	if (pf->width)
		str_maker(pf, ' ', pf->width);
	return (pf);
}

/*
** Right aligns the integer and saves it to final string.
** First checks for space flag, then width if there is no
** zero flag. Then negativity and plus flag. If there was
** zero flag and width, but not precision, saves width
** amount of zeroes. Then precision amount of zeroes and
** finally the integer string.
*/

static t_printf	*right_align_int(t_printf *pf, char *str_nbr)
{
	if (!(pf->neg) && !(pf->plus) && pf->space)
		str_maker(pf, ' ', 1);
	if (pf->width && !pf->zero)
		str_maker(pf, ' ', pf->width);
	if (pf->neg)
		str_maker(pf, '-', 1);
	else if (pf->plus)
		str_maker(pf, '+', 1);
	if (pf->width && pf->zero && !(pf->precision))
		str_maker(pf, '0', pf->width);
	if (pf->precision)
		str_maker(pf, '0', pf->precision);
	if (pf->nbrlen != 0)
		append_substr(pf, str_nbr, pf->nbrlen);
	return (pf);
}

/*
** Gets correct amount of width and precision.
** convert changes the number to a string, which is
** stored to str_nbr. Based on the nbrlen, we figure out
** correct amount of precision and then width.
** Calls left_aling_int or right_align_int depending if there
** is minus flag or not.
*/

static t_printf	*int_handler(t_printf *pf)
{
	char *str_nbr;

	str_nbr = convert(pf);
	pf->nbrlen = ft_strlen(str_nbr);
	if (pf->nbr == 0 && pf->precision == 0 && pf->prec_true == 1)
		pf->nbrlen = 0;
	pf->precision = pf->precision - pf->nbrlen;
	if (pf->precision < 0)
		pf->precision = 0;
	(pf->plus || pf->neg || pf->space) ?
	(pf->width = pf->width - pf->precision - pf->nbrlen - 1) :
	(pf->width = pf->width - pf->precision - pf->nbrlen);
	if (pf->prec_true && pf->zero)
		pf->zero = 0;
	if (pf->width < 0)
		pf->width = 0;
	(pf->minus) ? (left_align_int(pf, str_nbr)) :
	(right_align_int(pf, str_nbr));
	free(str_nbr);
	return (pf);
}

/*
** Gets the integer number from variable argument list.
** First checks for asterisk, then depending on type and
** length specifier, calls correct type of integer form
** the variable argument list. Sets the base to 10 and
** calls int_handler to get correct width and precision.
*/

t_printf		*di_op(t_printf *pf)
{
	if (pf->p_aste || pf->w_aste)
		get_asterisk(pf);
	if (pf->type == 'D')
		pf->nbr = (long int)va_arg(pf->args, long int);
	//else if (pf->length[0] == 'j')
	//	pf->nbr = (intmax_t)va_arg(pf->args, intmax_t);
	else if (pf->length[0] == 'z')
		pf->nbr = (size_t)va_arg(pf->args, size_t);
	else if (ft_strcmp(pf->length, "h") == 0)
		pf->nbr = (short int)va_arg(pf->args, int);
	else if (ft_strcmp(pf->length, "hh") == 0)
		pf->nbr = (signed char)va_arg(pf->args, int);
	else if (ft_strcmp(pf->length, "l") == 0)
		pf->nbr = (long int)va_arg(pf->args, long int);
	else if (ft_strcmp(pf->length, "ll") == 0)
		pf->nbr = (long long int)va_arg(pf->args, long long int);
	else
		pf->nbr = (int)va_arg(pf->args, int);
	pf->base = 10;
	int_handler(pf);
	return (pf);
}
