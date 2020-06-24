/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_op.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakela <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 17:52:16 by jmakela           #+#    #+#             */
/*   Updated: 2020/06/24 13:08:46 by jmakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** C_handler saves character to final string.
** First checks for alignment to decide whether
** width should be saved before or after the character
** and the type of width, if it is ' ' or 0.
*/

static t_printf	*c_handler(t_printf *pf)
{
	if (pf->width)
		pf->width = pf->width - 1;
	if (pf->minus)
	{
		str_maker(pf, pf->c, 1);
		if (pf->width)
			str_maker(pf, ' ', pf->width);
	}
	else
	{
		if (pf->width)
			(pf->zero) ? (str_maker(pf, '0', pf->width)) :
			(str_maker(pf, ' ', pf->width));
		str_maker(pf, pf->c, 1);
	}
	return (pf);
}

/*
** Gets character form variable argument list.
** First checks for asterisk, then gets the char.
** Calls c_handler to deal with flags and width.
*/

t_printf		*c_op(t_printf *pf)
{
	if (pf->p_aste || pf->w_aste)
		get_asterisk(pf);
	if (pf->length[0] != '\0')
	{
		write(2, "\033[31merror:\033[0m length not supported with c.\n", 45);
		exit(-1);
	}
	pf->c = (char)va_arg(pf->args, int);
	c_handler(pf);
	return (pf);
}
