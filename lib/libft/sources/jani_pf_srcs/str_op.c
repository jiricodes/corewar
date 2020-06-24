/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakela <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 18:44:22 by jmakela           #+#    #+#             */
/*   Updated: 2020/06/24 13:09:23 by jmakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Saves the string to final string.
** Depending on minus flag, the string is either
** before or after width. Checks if which type the
** width should be when saved ' ' or 0. Saves precision
** amount of string.
*/

static t_printf	*align_str(t_printf *pf)
{
	if (pf->minus)
	{
		append_substr(pf, pf->str, pf->precision);
		if (pf->width)
			str_maker(pf, ' ', pf->width);
	}
	else
	{
		if (pf->width)
		{
			(pf->zero) ? (str_maker(pf, '0', pf->width)) :
			(str_maker(pf, ' ', pf->width));
		}
		append_substr(pf, pf->str, pf->precision);
	}
	return (pf);
}

/*
** Finds out correct amount of width and precision.
** First checks if there string is null and duplicates
** "(null" to it, if it is. Then we take the length of
** the string and based to that, we decrement width and
** precision. Calls align_str to save the string, width
** and precision.
*/

static t_printf	*str_handler(t_printf *pf)
{
	if (pf->str == NULL)
		pf->str = ft_strdup("(null)");
	pf->nbrlen = ft_strlen((char*)pf->str);
	if (pf->precision > pf->nbrlen)
		pf->precision = pf->nbrlen;
	if (pf->precision)
		pf->width = pf->width - pf->precision;
	if (!(pf->prec_true))
	{
		pf->width = pf->width - pf->nbrlen;
		pf->precision = pf->nbrlen;
	}
	if (pf->width < 0)
		pf->width = 0;
	align_str(pf);
	return (pf);
}

/*
** Gets string from variable argument list.
** First checks for asterisk, then calls
** str_handler to get the string along with
** width and precision ready for saving.
*/

t_printf		*str_op(t_printf *pf)
{
	if (pf->p_aste || pf->w_aste)
		get_asterisk(pf);
	if (pf->length[0] != '\0')
	{
		write(2, "\033[31merror:\033[0m length not supported with s.\n", 45);
		exit(-1);
	}
	pf->str = (char*)va_arg(pf->args, char*);
	str_handler(pf);
	return (pf);
}
