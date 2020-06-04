/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_o.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 14:33:56 by jnovotny          #+#    #+#             */
/*   Updated: 2019/11/18 19:59:19 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** o Conversion
** The unsigned int argument is converted to unsigned octal notation.
** The precision, if any, gives the minimum number of digits that must
** appear; if the converted value requires fewer digits, it is padded
** on the left with zeros. The default precision is 1.
** When 0 is printed with an explicit precision 0, the output is empty.
*/

void	ft_process_o(t_format *f)
{
	unsigned long nb;

	nb = va_arg(f->list, long);
	if (f->len_mod == l || f->len_mod == ll)
	{
		if (nb == ULONG_MAX)
			f->out_str = ft_strdup("1777777777777777777777");
		else
			f->out_str = ft_ultoa_base((unsigned long)nb, 8, 0);
	}
	else if (f->len_mod == L || f->len_mod == nomod)
		f->out_str = ft_ultoa_base((unsigned int)nb, 8, 0);
	else if (f->len_mod == h)
		f->out_str = ft_ultoa_base((unsigned short)nb, 8, 0);
	else if (f->len_mod == hh)
		f->out_str = ft_ultoa_base((unsigned char)nb, 8, 0);
	else
		ft_error(f);
	ft_print_o(f);
	f->i++;
}

void	ft_print_o(t_format *f)
{
	char c;

	ft_prec_o(f);
	ft_hash_o(f);
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

void	ft_prec_o(t_format *f)
{
	char	*tmp;
	char	*res;
	size_t	len;

	if (f->out_str[0] == '0' && f->precision == 0 && !f->flag.hash)
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

void	ft_hash_o(t_format *f)
{
	char	*tmp;
	char	*res;

	if (f->flag.hash && f->out_str[0] != '0' && f->out_str[0] != '\0')
	{
		tmp = ft_strnew(1);
		tmp[0] = '0';
		res = ft_strjoin(tmp, f->out_str);
		free(f->out_str);
		free(tmp);
		f->out_str = res;
	}
}
