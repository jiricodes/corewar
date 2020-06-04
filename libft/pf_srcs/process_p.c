/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_p.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 12:14:13 by jnovotny          #+#    #+#             */
/*   Updated: 2019/11/18 19:03:45 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** The void * pointer argument is printed in hexadecimal
** (as if by %#x or %#lx).
*/

void	ft_process_p(t_format *f)
{
	long unsigned int nb;

	nb = (long unsigned int)va_arg(f->list, void*);
	f->out_str = ft_ultoa_base(nb, 16, 0);
	f->i++;
	ft_print_p(f);
}

void	ft_print_p(t_format *f)
{
	char c;

	ft_prec_p(f);
	ft_hash_p(f);
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

void	ft_prec_p(t_format *f)
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

void	ft_hash_p(t_format *f)
{
	char	*tmp;
	char	*res;

	if (!f->flag.zero)
	{
		tmp = ft_strnew(2);
		tmp[0] = '0';
		tmp[1] = 'x';
		res = ft_strjoin(tmp, f->out_str);
		free(f->out_str);
		free(tmp);
		f->out_str = res;
	}
	else if (f->flag.zero)
	{
		f->out_len += write(1, "0", 1);
		f->out_len += write(1, "x", 1);
		if (f->width)
			f->width -= 2;
	}
}
