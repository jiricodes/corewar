/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakela <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 19:00:57 by jmakela           #+#    #+#             */
/*   Updated: 2020/06/24 13:29:02 by jmakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Gets width and precision from variable argument list.
** Checks if width or precision asterisk is true, if it is,
** calls it from the variable argument list. and sets the
** width or precision to be equal to it.
*/

t_printf	*get_asterisk(t_printf *pf)
{
	int i;

	i = 0;
	if (pf->w_aste)
	{
		i = (int)va_arg(pf->args, int);
		pf->width = i;
	}
	if (pf->p_aste)
	{
		i = (int)va_arg(pf->args, int);
		pf->precision = i;
	}
	return (pf);
}

/*
** Saves % sign to the final string.
** Checks for alignment first and depending, saves
** % either first, or after width has been saved.
** Checks if there is width and if width has 0 flag.
** Saves appropriate amount of ' ' or 0.
*/

t_printf	*percent_op(t_printf *pf)
{
	if (pf->width)
		pf->width = pf->width - 1;
	if (pf->minus)
		str_maker(pf, '%', 1);
	if (pf->width)
	{
		if (pf->zero && !(pf->minus))
			str_maker(pf, '0', pf->width);
		else
			str_maker(pf, ' ', pf->width);
	}
	if (!(pf->minus))
		str_maker(pf, '%', 1);
	return (pf);
}

/*
** Saves the substring before or after %.
** If current position is 0 or saved position and
** current position is the same, we do nothing.
** Otherwise we make a substring from chars between
** current position and saved position and strjoin it
** to the final string, we count the total and free
** temporary string.
*/

int			append_subfmt(t_printf *pf)
{
	char *str;

	if (pf->i == 0 || pf->i == pf->pos)
		return (1);
	if (!(pf->temp = ft_strsub(pf->fmt_copy, pf->pos, ((pf->i) - pf->pos))))
		exit(-1);
	if (!(str = pf_strjoin(pf->final, pf->temp, pf->total, (pf->i) - pf->pos)))
		exit(-1);
	pf->total = pf->total + ((pf->i) - pf->pos);
	ft_strdel(&pf->final);
	pf->final = str;
	free(pf->temp);
	return (1);
}

/*
** Initializes all values for recording syntax.
** Init check being 0 creates masks used to recognize
** flags, length and type. Other than that there are
** various values used to store information about
** different flags, length of string, asterisks,
** precision existing, negativity etc.
*/

t_printf	*init_pf(t_printf *pf)
{
	if (pf->init_check == 0)
	{
		pf->flag_mask = "-+ 0#";
		pf->length_mask = "hlLzjt";
		pf->type_mask = "%cspdDioOuUxXfFb{";
	}
	pf->nbrlen = 0;
	pf->init_check = 1;
	pf->minus = 0;
	pf->plus = 0;
	pf->space = 0;
	pf->zero = 0;
	pf->hash = 0;
	pf->width = 0;
	pf->w_aste = 0;
	pf->precision = 0;
	pf->p_aste = 0;
	pf->prec_true = 0;
	pf->neg = 0;
	pf->length[0] = '\0';
	pf->length[1] = '\0';
	pf->length[2] = '\0';
	return (pf);
}
