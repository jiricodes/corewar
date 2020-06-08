/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_b.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 15:58:52 by jnovotny          #+#    #+#             */
/*   Updated: 2019/11/18 19:01:56 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** b Conversion
** The unsigned int argument is converted to unsigned binary notation.
** The precision, if any, gives the minimum number of digits that must
** appear; if the converted value requires fewer digits, it is padded
** on the left with zeros. The default precision is 1.
** When 0 is printed with an explicit precision 0, the output is empty.
*/

void	ft_process_b(t_format *f)
{
	long nb;

	nb = va_arg(f->list, long);
	if (f->len_mod == L || f->len_mod == nomod)
		f->out_str = ft_ultoa_base((unsigned int)nb, 2, 0);
	else if (f->len_mod == hh)
		f->out_str = ft_ultoa_base((unsigned char)nb, 2, 0);
	else if (f->len_mod == h)
		f->out_str = ft_ultoa_base((unsigned short)nb, 2, 0);
	else if (f->len_mod == l || f->len_mod == ll)
		f->out_str = ft_ultoa_base((unsigned long)nb, 2, 0);
	else
		ft_error(f);
	ft_print_b(f);
	f->i++;
}

void	ft_print_b(t_format *f)
{
	char c;

	ft_prec_b(f);
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
** Precision for 'o'
*/

void	ft_prec_b(t_format *f)
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
