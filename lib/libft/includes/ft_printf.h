/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakela <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 19:03:28 by jmakela           #+#    #+#             */
/*   Updated: 2020/06/24 13:11:30 by jmakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "libft.h"
# include "color.h"

typedef struct				s_printf
{
	va_list					args;
	char					*fmt_copy;
	char					*temp;
	char					*final;

	char					*flag_mask;
	char					*length_mask;
	char					*type_mask;
	int						init_check;

	size_t					pos;
	size_t					i;

	int						neg;

	int						minus;
	int						plus;
	int						space;
	int						zero;
	int						hash;

	int						w_aste;
	int						p_aste;

	long int				width;
	long int				precision;
	int						prec_true;
	char					length[3];
	char					type;

	char					c;
	char					*str;
	void					*ptr;
	long long int			nbr;
	unsigned long long int	unbr;
	long double				f_nbr;
	char					*whole;
	char					*rounded;
	size_t					total;

	int						nbrlen;
	int						base;
}							t_printf;

/*
** Different printf functions.
*/

int							ft_printf(const char *format, ...);
int							ft_dprintf(int fd, const char *format, ...);
int							ft_sprintf(char *buffer, const char *format, ...);

/*
** Parsing functions.
*/

t_printf					*parser(t_printf *pf);
t_printf					*parse_flags(t_printf *pf);
t_printf					*parse_width(t_printf *pf);
t_printf					*parse_preci(t_printf *pf);
t_printf					*parse_length(t_printf *pf);
t_printf					*parse_type(t_printf *pf);
t_printf					*parse_color(t_printf *pf, char *str);

/*
** Operations for various types.
*/

t_printf					*c_op(t_printf *pf);
t_printf					*str_op(t_printf *pf);
t_printf					*p_op(t_printf *pf);
t_printf					*di_op(t_printf *pf);
t_printf					*uox_op(t_printf *pf);
t_printf					*float_op(t_printf *pf);
t_printf					*percent_op(t_printf *pf);
t_printf					*get_asterisk(t_printf *pf);

/*
** String converters.
*/

char						*convert(t_printf *pf);
char						*u_convert(t_printf *pf);

/*
** Functions for saving various strings
** to the final string.
*/

t_printf					*append_substr(t_printf *pf, char *str, size_t len);
int							append_subfmt(t_printf *pf);
t_printf					*str_maker(t_printf *pf, char c, int count);

/*
** String handling functions.
*/

char						*pf_strjoin(
							char const *s1, char const *s2, int i, int j);
char						*pf_strcpy(char *dest, const char *src, size_t j);

/*
** Utilities.
*/

t_printf					*get_parts(t_printf *pf);
t_printf					*init_pf(t_printf *pf);
void						check_help(const char *format);
#endif
