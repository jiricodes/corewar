/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_xx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 12:36:44 by jnovotny          #+#    #+#             */
/*   Updated: 2019/11/18 19:06:22 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** x, X Conversion
** The unsigned int argument is converted to unsigned hexadecimal notation.
** The letters abcdef are used for x conversions; the letters ABCDEF
** are used for X conversions. The precision, if any, gives the minimum
** number of digits that must appear; if the converted value requires fewer
** digits, it is padded on the left with zeros. The default precision is 1.
** When 0 is printed with an explicit precision 0, the output is empty.
*/

void	ft_process_xx(t_format *f, const char *format)
{
	long nb;

	f->caps = format[f->i] == 'X' ? 1 : 0;
	nb = va_arg(f->list, long);
	if (f->len_mod == l || f->len_mod == ll || \
		f->len_mod == j || f->len_mod == z)
		f->out_str = ft_ultoa_base((unsigned long)nb, 16, f->caps);
	else if (f->len_mod == L || f->len_mod == nomod)
		f->out_str = ft_ultoa_base((unsigned int)nb, 16, f->caps);
	else if (f->len_mod == h)
		f->out_str = ft_ultoa_base((unsigned short)nb, 16, f->caps);
	else if (f->len_mod == hh)
		f->out_str = ft_ultoa_base((unsigned char)nb, 16, f->caps);
	else
		ft_error(f);
	ft_print_xx(f, format);
	f->i++;
}

void	ft_print_xx(t_format *f, const char *format)
{
	char c;

	ft_prec_xx(f);
	ft_hash_xx(f, format);
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
** Precision and Width for 'xX'
*/

void	ft_prec_xx(t_format *f)
{
	char	*tmp;
	char	*res;
	size_t	len;

	if (ft_isstrzero(f) && f->precision == 0)
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

void	ft_hash_xx(t_format *f, const char *format)
{
	char	*tmp;
	char	*res;

	if (ft_isstrzero(f) || f->out_str[0] == '\0')
		return ;
	if (f->flag.hash && !f->flag.zero)
	{
		tmp = ft_strnew(2);
		tmp[0] = '0';
		tmp[1] = format[f->i];
		res = ft_strjoin(tmp, f->out_str);
		free(f->out_str);
		free(tmp);
		f->out_str = res;
	}
	else if (f->flag.hash && f->flag.zero)
	{
		f->out_len += write(1, "0", 1);
		f->out_len += write(1, &format[f->i], 1);
		if (f->width)
			f->width -= 2;
	}
}

int		ft_isstrzero(t_format *f)
{
	size_t i;

	i = 0;
	while (f->out_str[i] != '\0')
	{
		if (f->out_str[i] != '0')
			return (0);
		i++;
	}
	return (1);
}
