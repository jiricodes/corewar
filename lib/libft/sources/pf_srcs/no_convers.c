/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_convers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 15:56:17 by jnovotny          #+#    #+#             */
/*   Updated: 2019/11/15 14:09:26 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** dealing with no conversion formatting printout;
*/

void	ft_process_no_convers(t_format *f, const char *format)
{
	f->out_str = ft_strnew(1);
	f->out_str[0] = format[f->i];
	if (f->out_str[0] != '\0')
	{
		f->i++;
		ft_print_no_convers(f);
	}
}

void	ft_print_no_convers(t_format *f)
{
	char c;

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
