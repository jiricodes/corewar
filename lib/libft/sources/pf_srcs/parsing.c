/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 10:44:15 by jnovotny          #+#    #+#             */
/*   Updated: 2019/11/18 09:36:17 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_reset_pf(t_format *f)
{
	bzero(&(f->flag), sizeof(t_flag));
	f->precision = -1;
	f->out_str = NULL;
	f->width = 0;
	f->len_mod = nomod;
	f->caps = 0;
}

void	ft_runflags(t_format *f, const char *format)
{
	flag_hash(f, format);
	flag_plus(f);
	flag_minus(f);
	flag_zero(f, format);
}

void	ft_getinfo(t_format *f, const char *format)
{
	while (ft_strchr(PF_STR, format[f->i]) && format[f->i] != '\0')
	{
		ft_getflag(f, format);
		ft_getwidth(f, format);
		ft_getprecision(f, format);
		ft_getlmod(f, format);
		ft_runflags(f, format);
		if (ft_strchr(PF_SKIP, format[f->i]) && format[f->i] != '\0')
			f->i++;
	}
}

void	ft_parse(t_format *f, const char *format)
{
	f->i++;
	ft_reset_pf(f);
	ft_getinfo(f, format);
	ft_create_out(f, format);
	if (f->out_str)
		free(f->out_str);
}
