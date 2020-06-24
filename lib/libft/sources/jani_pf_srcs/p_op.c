/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_op.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakela <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 18:27:25 by jmakela           #+#    #+#             */
/*   Updated: 2020/06/24 13:09:07 by jmakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Left aligns the pointer string to final string.
** Pointers have 0x in front of them, so that is
** appended first, then if there is precision,
** we save precision amount of zeroes, then the
** pointer string and finally width amount of ' '.
*/

static t_printf	*left_align_p(t_printf *pf, char *str_nbr)
{
	append_substr(pf, "0x", 2);
	if (pf->precision)
		str_maker(pf, '0', pf->precision);
	append_substr(pf, str_nbr, pf->nbrlen);
	if (pf->width)
		str_maker(pf, ' ', pf->width);
	return (pf);
}

/*
** Right aligns the pointer string to final string.
** Checks first for width and writes it if there is
** no zero flag, then appends 0x and if there was
** zero flag and width, then saves width amount of
** zeroes. Finally saves the pointer.
*/

static t_printf	*right_align_p(t_printf *pf, char *str_nbr)
{
	if (pf->width && ((!pf->zero || pf->prec_true)))
		str_maker(pf, ' ', pf->width);
	append_substr(pf, "0x", 2);
	if (pf->width && pf->zero && !(pf->prec_true))
		str_maker(pf, '0', pf->width);
	if (pf->precision)
		str_maker(pf, '0', pf->precision);
	append_substr(pf, str_nbr, pf->nbrlen);
	return (pf);
}

/*
** Finds out correct amounts of width and precision.
** u_convert changes the number to a string, which is
** stored to str_nbr. Based on the nbrlen, we figure out
** correct amount of precision and then width.
** Calls left_aling_p or right_align_p depending if there
** is minus flag or not.
*/

static t_printf	*p_handler(t_printf *pf)
{
	char *str_nbr;

	str_nbr = u_convert(pf);
	pf->nbrlen = ft_strlen(str_nbr);
	if (pf->prec_true && pf->precision == 0 && pf->unbr == 0)
		pf->nbrlen = 0;
	pf->precision = pf->precision - pf->nbrlen;
	if (pf->precision < 0)
		pf->precision = 0;
	pf->width = pf->width - pf->nbrlen - pf->precision - 2;
	if (pf->width < 0)
		pf->width = 0;
	(pf->minus) ? (left_align_p(pf, str_nbr)) :
	(right_align_p(pf, str_nbr));
	free(str_nbr);
	return (pf);
}

/*
** Gets pointer from variable argument list.
** First checks for asterisk, then gets the pointer
** as unsigned int, sets the base value to 16, since
** pointer address is in hex. Calls p_handler to put
** width and precision to correct values.
*/

t_printf		*p_op(t_printf *pf)
{
	if (pf->p_aste || pf->w_aste)
		get_asterisk(pf);
	if (pf->length[0] != '\0')
	{
		write(2, "\033[31merror:\033[0m length not supported with p.\n", 45);
		exit(-1);
	}
	pf->unbr = (unsigned long int)va_arg(pf->args, unsigned long int);
	pf->base = 16;
	p_handler(pf);
	return (pf);
}
