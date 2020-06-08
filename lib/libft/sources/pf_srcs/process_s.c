/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_s.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 15:48:55 by jnovotny          #+#    #+#             */
/*   Updated: 2019/11/18 19:02:27 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** s Conversion
** If no l modifier is present: the const char * argument is
** expected to be a pointer to an array of character type
** (pointer to a string). Characters from the array are written
** up to (but not including) a terminating null byte ('\0'); if a
** precision is specified, no more than the number specified are
** written.  If a precision is given, no null byte need be
** present; if the precision is not specified, or is greater than
** the size of the array, the array must contain a terminating
** null byte.
*/

void	ft_process_s(t_format *f)
{
	char *str;

	str = va_arg(f->list, char*);
	f->i++;
	if (!str)
		str = "(null)";
	if (f->precision >= 0 && f->precision < (int)ft_strlen(str))
		f->out_str = ft_strsub(str, 0, f->precision);
	else
		f->out_str = ft_strdup(str);
	ft_print_s(f);
}

void	ft_print_s(t_format *f)
{
	char c;

	if (f->width > (int)ft_strlen(f->out_str))
	{
		c = f->flag.zero ? '0' : ' ';
		if (f->flag.minus)
		{
			f->out_len += write(1, f->out_str, ft_strlen(f->out_str));
			while ((f->width--) - ft_strlen(f->out_str) > 0)
				f->out_len += write(1, &c, 1);
		}
		else
		{
			while ((f->width--) - ft_strlen(f->out_str) > 0)
				f->out_len += write(1, &c, 1);
			f->out_len += write(1, f->out_str, ft_strlen(f->out_str));
		}
	}
	else
		f->out_len += write(1, f->out_str, ft_strlen(f->out_str));
}
