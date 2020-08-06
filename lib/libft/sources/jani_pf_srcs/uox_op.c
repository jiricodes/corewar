/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uox_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 18:52:22 by jmakela           #+#    #+#             */
/*   Updated: 2020/08/06 15:02:05 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Left aligns uox number for final string.
** First checks for hash depending on type and
** saves the correct prefix. Then saves precision
** amount of zeroes, then the uox number string and
** finally width amount of spaces.
*/

static t_printf	*left_align_uox(t_printf *pf, char *str_nbr)
{
	if ((pf->type == 'o' || pf->type == 'O') &&
		!(pf->precision) && pf->hash && pf->unbr != 0)
		str_maker(pf, '0', 1);
	else if ((pf->type == 'o' || pf->type == 'O') &&
		!(pf->precision) && pf->prec_true && pf->hash && pf->unbr == 0)
		str_maker(pf, '0', 1);
	else if (pf->type == 'x' && pf->hash && pf->unbr != 0)
		append_substr(pf, "0x", 2);
	else if (pf->type == 'X' && pf->hash && pf->unbr != 0)
		append_substr(pf, "0X", 2);
	if (pf->precision)
		str_maker(pf, '0', pf->precision);
	if (pf->nbrlen != 0)
		append_substr(pf, str_nbr, pf->nbrlen);
	if (pf->width)
		str_maker(pf, ' ', pf->width);
	return (pf);
}

/*
** Right aligns uox number for final string.
** First checks for width if there is no zero and
** saves width amount of spaces. Then saves depending
** on type and hash, different prefix. Then checks if
** there was width with zero flag and after that precision.
** Finally saves the uox number string into final string.
*/

static t_printf	*right_align_uox(t_printf *pf, char *str_nbr)
{
	if (pf->width && !(pf->zero))
		str_maker(pf, ' ', pf->width);
	if ((pf->type == 'o' || pf->type == 'O') &&
		!(pf->precision) && pf->hash && pf->unbr != 0)
		str_maker(pf, '0', 1);
	else if ((pf->type == 'o' || pf->type == 'O') &&
		!(pf->precision) && pf->prec_true && pf->hash && pf->unbr == 0)
		str_maker(pf, '0', 1);
	else if (pf->type == 'x' && pf->hash && pf->unbr != 0)
		append_substr(pf, "0x", 2);
	else if (pf->type == 'X' && pf->hash && pf->unbr != 0)
		append_substr(pf, "0X", 2);
	if (pf->width && pf->zero && !(pf->prec_true))
		str_maker(pf, '0', pf->width);
	if (pf->precision)
		str_maker(pf, '0', pf->precision);
	if (pf->nbrlen != 0)
		append_substr(pf, str_nbr, pf->nbrlen);
	return (pf);
}

/*
** Gets correct amount of width and precision.
** u_convert changes the number to a string, which is
** stored to str_nbr. Based on the nbrlen, we figure out
** correct amount of precision and then width. Different
** types have different width since they have prefixes.
** Calls left_aling_int or right_align_int depending if there
** is minus flag or not.
*/

static t_printf	*uox_handler(t_printf *pf)
{
	char *str_nbr;

	str_nbr = u_convert(pf);
	pf->nbrlen = ft_strlen(str_nbr);
	if (pf->unbr == 0 && pf->precision == 0 && pf->prec_true == 1)
		pf->nbrlen = 0;
	pf->precision = pf->precision - pf->nbrlen;
	if (pf->precision < 0)
		pf->precision = 0;
	pf->width = pf->width - pf->precision - pf->nbrlen;
	if ((pf->type == 'o' || pf->type == 'O') &&
		pf->hash && pf->unbr != 0 && pf->precision == 0)
		pf->width = pf->width - 1;
	else if ((pf->type == 'o' || pf->type == 'O') &&
		pf->hash && pf->unbr == 0 && pf->precision == 0 && pf->prec_true)
		pf->width = pf->width - 1;
	else if ((pf->type == 'x' || pf->type == 'X') &&
		pf->hash && pf->unbr != 0)
		pf->width = pf->width - 2;
	(pf->width < 0) ? (pf->width = 0) : 0;
	(pf->prec_true && pf->zero) ? (pf->zero = 0) : 0;
	(pf->minus) ? (left_align_uox(pf, str_nbr)) :
	(right_align_uox(pf, str_nbr));
	free(str_nbr);
	return (pf);
}

/*
** Gets unsigned integer number from variable argumment list.
** First checks for asterisk and then gets the correct type
** of value from variable argument list based on type and length.
** Sets the base to 10 for u/U, 8 for o/O, 16 for x/X and 2 for b.
** Calls uox_handler to get correct width and precision.
*/

t_printf		*uox_op(t_printf *pf)
{
	if (pf->p_aste || pf->w_aste)
		get_asterisk(pf);
	if (pf->type == 'U' || pf->type == 'O')
		pf->unbr = (unsigned long int)va_arg(pf->args, unsigned long int);
	else if (pf->length[0] == 'j')
		pf->unbr = (uintmax_t)va_arg(pf->args, uintmax_t);
	else if (pf->length[0] == 'z')
		pf->unbr = (size_t)va_arg(pf->args, size_t);
	else if (ft_strcmp(pf->length, "h") == 0)
		pf->unbr = (unsigned short int)va_arg(pf->args, unsigned int);
	else if (ft_strcmp(pf->length, "hh") == 0)
		pf->unbr = (unsigned char)va_arg(pf->args, unsigned int);
	else if (ft_strcmp(pf->length, "l") == 0)
		pf->unbr = (unsigned long int)va_arg(pf->args, unsigned long int);
	else if (ft_strcmp(pf->length, "ll") == 0)
		pf->unbr =
		(unsigned long long int)va_arg(pf->args, unsigned long long int);
	else
		pf->unbr = (unsigned int)va_arg(pf->args, unsigned int);
	pf->base = 10;
	(pf->type == 'o' || pf->type == 'O') ? (pf->base = 8) : 0;
	(pf->type == 'x' || pf->type == 'X') ? (pf->base = 16) : 0;
	(pf->type == 'b') ? (pf->base = 2) : 0;
	uox_handler(pf);
	return (pf);
}
