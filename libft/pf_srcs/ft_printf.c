/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 17:33:10 by jnovotny          #+#    #+#             */
/*   Updated: 2019/11/19 17:46:43 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_dump(t_format *f, const char *format)
{
	int			len;

	len = 0;
	while (FIL != '%' && FIL != '{' && FIL != '\0')
		len++;
	f->out_len += write(1, &format[f->i], len);
	f->i += len;
}

int		ft_printf(const char *format, ...)
{
	t_format	f;

	ft_bzero(&f, sizeof(t_format));
	va_start(f.list, format);
	while (format[f.i] != '\0')
	{
		if (format[f.i] == '%' && format[f.i + 1] != '%')
			format[f.i + 1] == '\0' ? f.i++ : ft_parse(&f, format);
		else if (format[f.i] == '%' && format[f.i + 1] == '%')
		{
			f.out_len = f.out_len + write(1, "%", 1);
			f.i = f.i + 2;
		}
		else if (format[f.i] == '{')
			ft_settings(&f, format);
		else
			ft_dump(&f, format);
	}
	va_end(f.list);
	return (f.out_len);
}
