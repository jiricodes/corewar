/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_c.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 12:06:44 by jnovotny          #+#    #+#             */
/*   Updated: 2019/11/18 19:00:11 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** c Conversion
** If no l modifier is present, the int argument is converted to an unsigned
** char, and the resulting character is written.  If an l modifier is present,
** the wint_t (wide character) argument is converted to a multibyte sequence
** by a call to the wcrtomb(3) function, with a conversion state starting
** in the initial state, and the resulting multibyte string is written.
*/

void	ft_process_c(t_format *f)
{
	int		nb;
	wint_t	c;

	if (f->len_mod == l)
	{
		c = va_arg(f->list, wint_t);
		f->out_str = ft_strnew(1);
		f->out_str[0] = c;
	}
	else
	{
		nb = va_arg(f->list, int);
		f->out_str = ft_strnew(1);
		f->out_str[0] = (unsigned char)nb;
	}
	f->i++;
	if (f->out_str == NULL)
		f->out_str[0] = 0;
	ft_print_c(f);
}

void	ft_print_c(t_format *f)
{
	char c;

	if (f->width > 1)
	{
		c = f->flag.zero ? '0' : ' ';
		if (f->flag.minus)
		{
			f->out_len += f->out_str[0] != 0 ? write(1, f->out_str, \
				ft_strlen(f->out_str)) : write(1, "\0", 1);
			while ((f->width--) - 1 > 0)
				f->out_len += write(1, &c, 1);
		}
		else
		{
			while ((f->width--) - 1 > 0)
				f->out_len += write(1, &c, 1);
			f->out_len += f->out_str[0] != 0 ? write(1, f->out_str, \
				ft_strlen(f->out_str)) : write(1, "\0", 1);
		}
	}
	else
		f->out_len += f->out_str[0] != 0 ? write(1, f->out_str, \
		ft_strlen(f->out_str)) : write(1, "\0", 1);
}
