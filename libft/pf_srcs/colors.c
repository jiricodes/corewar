/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 11:46:33 by jnovotny          #+#    #+#             */
/*   Updated: 2019/11/19 17:25:44 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_settings(t_format *f, const char *format)
{
	ft_setcolor(f, format);
	ft_setfont(f, format);
}

void	ft_setcolor(t_format *f, const char *format)
{
	if (ft_strnequ(&format[f->i], "{RED}", 5))
	{
		f->out_len += write(1, C_RED, 5);
		f->i += 5;
	}
	else if (ft_strnequ(&format[f->i], "{GREEN}", 7))
	{
		f->out_len += write(1, C_GREEN, 5);
		f->i += 7;
	}
	else if (ft_strnequ(&format[f->i], "{YELLOW}", 8))
	{
		f->out_len += write(1, C_YELLOW, 5);
		f->i += 8;
	}
	else
		ft_setcolor2(f, format);
}

void	ft_setcolor2(t_format *f, const char *format)
{
	if (ft_strnequ(&format[f->i], "{BLUE}", 6))
	{
		f->out_len += write(1, C_BLUE, 5);
		f->i += 6;
	}
	else if (ft_strnequ(&format[f->i], "{PURPLE}", 8))
	{
		f->out_len += write(1, C_PURPLE, 5);
		f->i += 8;
	}
	else if (ft_strnequ(&format[f->i], "{CYAN}", 6))
	{
		f->out_len += write(1, C_CYAN, 5);
		f->i += 6;
	}
	else if (ft_strnequ(&format[f->i], "{EOC}", 5))
	{
		f->out_len += write(1, C_EOC, 5);
		f->i += 5;
	}
}

void	ft_setfont(t_format *f, const char *format)
{
	if (ft_strnequ(&format[f->i], "{B}", 3))
	{
		f->out_len += write(1, F_BOLD, 5);
		f->i += 3;
	}
	else if (ft_strnequ(&format[f->i], "{LIGHT}", 7))
	{
		f->out_len += write(1, F_LIGHT, 5);
		f->i += 7;
	}
	else if (ft_strnequ(&format[f->i], "{I}", 3))
	{
		f->out_len += write(1, F_ITALIC, 5);
		f->i += 3;
	}
	else if (ft_strnequ(&format[f->i], "{U}", 3))
	{
		f->out_len += write(1, F_UNDERLINE, 5);
		f->i += 3;
	}
	else
		ft_setfont2(f, format);
}

void	ft_setfont2(t_format *f, const char *format)
{
	if (ft_strnequ(&format[f->i], "{BLINK}", 7))
	{
		f->out_len += write(1, F_BLINK, 5);
		f->i += 7;
	}
	else if (ft_strnequ(&format[f->i], "{INV}", 5))
	{
		f->out_len += write(1, F_INVERT, 5);
		f->i += 5;
	}
	else if (ft_strnequ(&format[f->i], "{STR}", 5))
	{
		f->out_len += write(1, F_STRIKE, 5);
		f->i += 5;
	}
	else if (ft_strnequ(&format[f->i], "{RST}", 5))
	{
		f->out_len += write(1, F_RESET, 5);
		f->i += 5;
	}
	else if (format[f->i] == '{')
	{
		f->out_len += write(1, "{", 1);
		f->i += 1;
	}
}
