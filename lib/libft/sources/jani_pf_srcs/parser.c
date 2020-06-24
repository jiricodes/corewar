/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakela <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 18:41:06 by jmakela           #+#    #+#             */
/*   Updated: 2020/06/24 13:09:17 by jmakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Initializes the current position in the format string,
** position used for creation of substring, total amount
** characters written, init_check, which is used to
** initialize masks and we allocate final string.
*/

static t_printf	*init_start(t_printf *pf)
{
	pf->i = 0;
	pf->pos = 0;
	pf->total = 0;
	pf->init_check = 0;
	pf->final = ft_strnew(1);
	return (pf);
}

/*
** Based on the type, appropriate operation is called.
** If no operation is found (the case of wrong syntax),
** we simply keep going and don't print anything of the
** wrong syntax.
*/

static t_printf	*choose_op(t_printf *pf)
{
	if (pf->type == '%')
		percent_op(pf);
	else if (pf->type == 'c')
		c_op(pf);
	else if (pf->type == 's')
		str_op(pf);
	else if (pf->type == 'p')
		p_op(pf);
	else if (pf->type == 'd' || pf->type == 'i' || pf->type == 'D')
		di_op(pf);
	else if (pf->type == 'u' || pf->type == 'U' || pf->type == 'o' ||
			pf->type == 'O' || pf->type == 'x' || pf->type == 'X' ||
			pf->type == 'b')
		uox_op(pf);
	else if (pf->type == 'f' || pf->type == 'F')
		float_op(pf);
	else if (pf->type == '{')
		parse_color(pf, pf->fmt_copy + pf->i);
	return (pf);
}

/*
** Parser first initializes some of the values needed.
** Then it starts to move through the format string
** until it finds %. Once that is found, parsing begins.
** First we save the substring before %, then we initialize
** all string modifiers, flags, width, precision, type, etc.
** Then in order we check for flags, width, precision, length
** and type. Existence of each specifier is saved to the struct.
** Then we chooce which operation should be performed.
*/

t_printf		*parser(t_printf *pf)
{
	init_start(pf);
	while (pf->fmt_copy[pf->i])
	{
		if (pf->fmt_copy[pf->i] == '%')
		{
			append_subfmt(pf);
			init_pf(pf);
			parse_flags(pf);
			parse_width(pf);
			parse_preci(pf);
			parse_length(pf);
			parse_type(pf);
			choose_op(pf);
			if (pf->fmt_copy[pf->i] == '\0')
				return (pf);
		}
		pf->i = pf->i + 1;
	}
	append_subfmt(pf);
	return (pf);
}
