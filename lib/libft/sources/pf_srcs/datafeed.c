/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   datafeed.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 14:06:03 by jnovotny          #+#    #+#             */
/*   Updated: 2019/11/19 18:06:44 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_getflag(t_format *f, const char *format)
{
	while (ft_strchr(FLAG_STR, format[f->i]) && format[f->i] != '\0')
	{
		if (format[f->i] == '0')
			f->flag.zero = 1;
		else if (format[f->i] == '#')
			f->flag.hash = 1;
		else if (format[f->i] == '+')
			f->flag.plus = 1;
		else if (format[f->i] == '-')
			f->flag.minus = 1;
		else if (format[f->i] == ' ')
			f->flag.space = 1;
		else if (format[f->i] == '*')
			f->width = (int)va_arg(f->list, long);
		format[f->i] != '\0' ? f->i++ : ft_error(f);
	}
}

void	ft_getwidth(t_format *f, const char *format)
{
	if (ft_isdigit(format[f->i]))
		f->width = ft_atoi(&format[f->i]);
	while (ft_isdigit(format[f->i]))
		f->i++;
}

void	ft_getprecision(t_format *f, const char *format)
{
	if (format[f->i] == '.')
	{
		f->i++;
		if (format[f->i] == '*')
		{
			f->precision = (int)va_arg(f->list, long);
			f->i++;
		}
		else
		{
			f->precision = ft_atoi(&format[f->i]);
			while (ft_isdigit(format[f->i]))
				f->i++;
		}
	}
}

void	ft_getlmod(t_format *f, const char *format)
{
	if (format[f->i] == 'h' && format[f->i + 1] == 'h')
	{
		f->len_mod < hh ? f->len_mod = hh : 0;
		f->i++;
	}
	else if (format[f->i] == 'l' && format[f->i + 1] == 'l')
	{
		f->len_mod < ll ? f->len_mod = ll : 0;
		f->i++;
	}
	else if (format[f->i] == 'l' && format[f->i + 1] != 'l')
		f->len_mod < l ? f->len_mod = l : 0;
	else if (format[f->i] == 'h' && format[f->i + 1] != 'h')
		f->len_mod < h ? f->len_mod = h : 0;
	else if (format[f->i] == 'L')
		f->len_mod < L ? f->len_mod = L : 0;
	else if (format[f->i] == 'j')
		f->len_mod < j ? f->len_mod = j : 0;
	else if (format[f->i] == 'z')
		f->len_mod < z ? f->len_mod = z : 0;
	if (ft_strchr(PF_LEN, format[f->i]))
		format[f->i] != '\0' ? f->i++ : ft_error(f);
}
