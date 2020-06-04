/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_u.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 16:10:04 by jnovotny          #+#    #+#             */
/*   Updated: 2019/11/18 19:08:13 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** u Conversion
** The unsigned int argument is converted to unsigned decimal notation.
** The precision, if any, gives the minimum number of digits that must appear;
** if the converted value requires fewer digits, it is padded on the left
**  with zeros.  The default precision is 1.
** When 0 is printed with an explicit precision 0, the output is empty.
*/

void	ft_process_u(t_format *f, const char *format)
{
	long nb;

	nb = va_arg(f->list, long);
	f->i++;
	if (f->len_mod == l || f->len_mod == ll || f->len_mod == j || \
		f->len_mod == z || format[f->i - 1] == 'U')
		f->out_str = ft_ultoa(nb);
	else if (f->len_mod == L || f->len_mod == nomod)
		f->out_str = ft_uitoa((unsigned int)nb);
	else if (f->len_mod == h)
		f->out_str = ft_uitoa((unsigned short)nb);
	else if (f->len_mod == hh)
		f->out_str = ft_uitoa((unsigned char)nb);
	else
		ft_error(f);
	ft_print_u(f);
}

void	ft_print_u(t_format *f)
{
	char c;

	ft_prec_u(f);
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

/*
** Precision and Width for 'di'
*/

void	ft_prec_u(t_format *f)
{
	char	*tmp;
	char	*res;
	size_t	len;

	if (f->out_str[0] == '0' && f->precision == 0)
		f->out_str[0] = '\0';
	else if (f->precision > (int)ft_strlen(f->out_str))
	{
		len = f->precision - ft_strlen(f->out_str);
		tmp = ft_strnew(len);
		ft_memset((void*)tmp, 48, len);
		res = ft_strjoin(tmp, f->out_str);
		free(f->out_str);
		free(tmp);
		f->out_str = res;
	}
}
