/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_f.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 16:28:51 by jnovotny          #+#    #+#             */
/*   Updated: 2019/11/18 19:07:44 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** f Conversion
** The double argument is rounded and converted to decimal notation
** in the style [-]ddd.ddd, where the number of digits after
** the decimal-point character is equal to the precision specification.
** If the precision is missing, it is taken as 6; if the precision is
** explicitly zero, no decimal-point character appears.
** If a decimal point appears, at least one digit appears before it.
*/

void	ft_process_f(t_format *f)
{
	long double	nbl;
	double		nb;

	if (f->len_mod == L)
	{
		nbl = (long double)va_arg(f->list, long double);
		f->out_str = ft_lftoa(nbl, f->precision == -1 ? 6 : f->precision);
	}
	else
	{
		nb = (double)va_arg(f->list, double);
		f->out_str = ft_lftoa(nb, f->precision == -1 ? 6 : f->precision);
	}
	ft_print_f(f);
	f->i++;
}

void	ft_print_f(t_format *f)
{
	char c;

	ft_hash_f(f);
	ft_sign_f(f);
	ft_add_sign_f(f);
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

void	ft_sign_f(t_format *f)
{
	char	*tmp;

	if (f->out_str[0] == '-')
	{
		tmp = ft_strdup(f->out_str + 1);
		free(f->out_str);
		f->out_str = tmp;
		f->flag.plus = 0;
		f->flag.sign = -1;
	}
	else
		f->flag.sign = 1;
}

void	ft_add_sign_f(t_format *f)
{
	char *tmp;
	char *res;
	char sign;

	if ((f->flag.plus || f->flag.sign == -1 || f->flag.space) && !f->flag.zero)
	{
		tmp = ft_strnew(1);
		tmp[0] = f->flag.plus ? '+' : ' ';
		f->flag.sign == -1 ? tmp[0] = '-' : 0;
		res = ft_strjoin(tmp, f->out_str);
		free(f->out_str);
		free(tmp);
		f->out_str = res;
	}
	else if ((f->flag.plus || f->flag.sign == -1 || \
		f->flag.space) && f->flag.zero)
	{
		sign = f->flag.plus ? '+' : ' ';
		f->flag.sign == -1 ? sign = '-' : 0;
		f->out_len += write(1, &sign, 1);
		f->width ? f->width-- : 0;
	}
}

void	ft_hash_f(t_format *f)
{
	size_t i;

	i = ft_strlen(f->out_str) - 1;
	if (!f->flag.hash && f->out_str[i] == '.')
		f->out_str[i] = '\0';
}
