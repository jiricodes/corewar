/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_basic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 12:22:33 by jnovotny          #+#    #+#             */
/*   Updated: 2019/11/15 14:07:24 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** # Hashtag
** For 'o' conversions, the first character of the output string is made
** zero (by prefixing a 0 if it was not zero already).
** For x and X conversions, a nonzero result has the string "0x" or "0X"
** prepended to it.
** For a, A, e, E, f, F, g, and G conversions, the result will always
** contain a decimal point
** For g and G conversions, trailing zeros are not removed from the result
** as they would otherwise be.
** For other conversions, the result is undefined.
*/

void	flag_hash(t_format *f, const char *format)
{
	if (!f->flag.hash)
		return ;
	if (ft_strchr(F_HASH_ERR, format[f->i]))
		f->flag.hash = 0;
}

/*
** 0 Zero
** The value should be zero padded.  For d, i, o, u, x, X, a, A,
** e, E, f, F, g, and G conversions, the converted value is
** padded on the left with zeros rather than blanks.
** If the 0 and - flags both appear, the 0 flag is ignored.
** If a precision is given with a numeric conversion
** (d, i, o, u, x, and X), the 0 flag is ignored.
** For other conversions, the behavior is undefined.
*/

void	flag_zero(t_format *f, const char *format)
{
	(f->precision >= 0 && ft_strchr(F_ZERO_NUM, format[f->i])) ?\
		f->flag.zero = 0 : 0;
}

/*
** + Plus
** A sign (+ or -) should always be placed before a number produced by
** a signed conversion. A + overrides a space if both are used.
*/

void	flag_plus(t_format *f)
{
	f->flag.plus && f->flag.space ? f->flag.space = 0 : 0;
}

/*
** - Minus
** The converted value is to be left adjusted on the field boundary.
** The converted value is padded on the right with blanks,
** rather than on the left with blanks or zeros.
** A - overrides a 0 if both are given.
*/

void	flag_minus(t_format *f)
{
	f->flag.minus ? f->flag.zero = 0 : 0;
}

/*
** ' ' Space
** A blank should be left before a positive number (or
** empty string) produced by a signed conversion.
*/
