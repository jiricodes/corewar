/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 17:29:51 by jnovotny          #+#    #+#             */
/*   Updated: 2019/11/19 17:45:34 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include "my_strform.h"
# include <stdio.h>
# include <stdarg.h>
# include <wchar.h>

# define FLAG_STR "0#+- *"
# define F_HASH_ERR "bdiucsCSpnm"
# define F_ZERO_ERR "csCSpnm"
# define F_ZERO_NUM "bdiouxX"
# define C_STR "bcdifopsuxX"
# define PF_STR "0123456789.#+- hlLqjzt*"
# define PF_LEN "hlLjz"
# define PF_SKIP "qt"
# define FIL format[f->i + len]

/*
** Flag management struct
*/

typedef struct	s_flag
{
	char	zero;
	char	hash;
	char	plus;
	char	minus;
	char	space;
	char	sign;
}				t_flag;

/*
** Lenght modifier struct
*/

typedef enum	e_lmod
{
	nomod = 0,
	hh,
	h,
	L,
	l,
	ll,
	z,
	j
}				t_lmod;

/*
** Core format struct
*/

typedef struct	s_format
{
	va_list list;
	char	*out_str;
	size_t	out_len;
	size_t	i;
	t_flag	flag;
	int		width;
	int		precision;
	t_lmod	len_mod;
	int		caps;
}				t_format;

/*
** Core Logistics
*/

int				ft_printf(const char *format, ...);
void			ft_dump(t_format *f, const char *format);
void			ft_parse(t_format *f, const char *format);
void			ft_getinfo(t_format *f, const char *format);
void			ft_reset_pf(t_format *f);
void			ft_error(t_format *f);

/*
**	Information fetching
*/

void			ft_getflag(t_format *f, const char *format);
void			ft_getwidth(t_format *f, const char *format);
void			ft_getprecision(t_format *f, const char *format);
void			ft_getlmod(t_format *f, const char *format);

/*
**	Output generators
*/

void			ft_create_out(t_format *f, const char *format);

/*
** Flags
*/

void			ft_runflags(t_format *f, const char *format);
void			flag_hash(t_format *f, const char *format);
void			flag_zero(t_format *f, const char *format);
void			flag_plus(t_format *f);
void			flag_minus(t_format *f);
void			flag_space(t_format *f, const char *format);

/*
** Conversions
*/

void			ft_process_di(t_format *f);
void			ft_process_xx(t_format *f, const char *format);
void			ft_process_o(t_format *f);
void			ft_process_b(t_format *f);
void			ft_process_u(t_format *f, const char *format);
void			ft_process_f(t_format *f);
void			ft_process_c(t_format *f);
void			ft_process_s(t_format *f);
void			ft_process_p(t_format *f);
void			ft_process_no_convers(t_format *f, const char *format);

/*
**	Printers
*/

void			ft_print_di(t_format *f);
void			ft_print_xx(t_format *f, const char *format);
void			ft_print_o(t_format *f);
void			ft_print_b(t_format *f);
void			ft_print_u(t_format *f);
void			ft_print_f(t_format *f);
void			ft_print_c(t_format *f);
void			ft_print_s(t_format *f);
void			ft_print_p(t_format *f);
void			ft_print_no_convers(t_format *f);

/*
**	di - tools
*/

void			ft_prec_di(t_format *f);
void			ft_sign(t_format *f);
void			ft_add_sign(t_format *f);

/*
** xX - tools
*/

void			ft_prec_xx(t_format *f);
void			ft_hash_xx(t_format *f, const char *format);
int				ft_isstrzero(t_format *f);

/*
** o - tools
*/

void			ft_prec_o(t_format *f);
void			ft_hash_o(t_format *f);

/*
** b - tools
*/

void			ft_prec_b(t_format *f);

/*
** u - tools
*/

void			ft_prec_u(t_format *f);

/*
** p - tools
*/

void			ft_hash_p(t_format *f);
void			ft_prec_p(t_format *f);

/*
** f - tools
*/

void			ft_sign_f(t_format *f);
void			ft_add_sign_f(t_format *f);
void			ft_hash_f(t_format *f);

/*
** Text Format
*/

void			ft_settings(t_format *f, const char *format);
void			ft_setcolor(t_format *f, const char *format);
void			ft_setcolor2(t_format *f, const char *format);
void			ft_setfont(t_format *f, const char *format);
void			ft_setfont2(t_format *f, const char *format);

#endif
