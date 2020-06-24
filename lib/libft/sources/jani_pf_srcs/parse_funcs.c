/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakela <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 18:38:07 by jmakela           #+#    #+#             */
/*   Updated: 2020/06/24 13:09:14 by jmakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Flag parsing function.
** While loop cycles through the flag_mask string that
** has all the flags, whenever we run into a correct flag
** we save it to the struct as 1, flag is true.
*/

t_printf	*parse_flags(t_printf *pf)
{
	int i;

	i = 0;
	pf->i = pf->i + 1;
	while (pf->flag_mask[i] != '\0')
	{
		while (pf->flag_mask[i] == pf->fmt_copy[pf->i])
		{
			while (pf->fmt_copy[pf->i] == '-' && pf->i++)
				pf->minus = 1;
			while (pf->fmt_copy[pf->i] == '+' && pf->i++)
				pf->plus = 1;
			while (pf->fmt_copy[pf->i] == ' ' && pf->i++)
				pf->space = 1;
			while (pf->fmt_copy[pf->i] == '0' && pf->i++)
				pf->zero = 1;
			while (pf->fmt_copy[pf->i] == '#' && pf->i++)
				pf->hash = 1;
			i = 0;
		}
		i = i + 1;
	}
	return (pf);
}

/*
** Width parsing function.
** First we check if there happens to be asterisk.
** If there is, we mark width asterisk being true and move onwards.
** If there is no asterisk, we keep going as long as we find digits
** Digits are saved to the width as we keep going.
*/

t_printf	*parse_width(t_printf *pf)
{
	if (pf->fmt_copy[pf->i] == '*')
	{
		pf->w_aste = 1;
		pf->i = pf->i + 1;
	}
	else
	{
		while (ft_isdigit(pf->fmt_copy[pf->i]))
		{
			pf->width = pf->width * 10 + (pf->fmt_copy[pf->i] - 48);
			pf->i = pf->i + 1;
		}
	}
	return (pf);
}

/*
** Precision parsing function.
** Checks for dot, if it not found, there was no precision.
** However if dot is found, then we check for asterisk and
** mark precision being true. If asterisk if is foud we move
** forwards, if it is not found, then we check for digits and keep saving
** them to precision.
*/

t_printf	*parse_preci(t_printf *pf)
{
	if (pf->fmt_copy[pf->i] == '.')
	{
		pf->prec_true = 1;
		pf->i = pf->i + 1;
		if (pf->fmt_copy[pf->i] == '*')
		{
			pf->p_aste = 1;
			pf->i = pf->i + 1;
		}
		else
		{
			while (ft_isdigit(pf->fmt_copy[pf->i]))
			{
				pf->precision = pf->precision * 10 + (pf->fmt_copy[pf->i] - 48);
				pf->i = pf->i + 1;
			}
		}
	}
	return (pf);
}

/*
** Length parsing function.
** While loop goes through length mask and checks if matching
** character is found, if it is, then it is saved to the length.
*/

t_printf	*parse_length(t_printf *pf)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (pf->length_mask[i] != '\0')
	{
		while (pf->length_mask[i] == pf->fmt_copy[pf->i])
		{
			if (j < 2)
				pf->length[j] = pf->length_mask[i];
			pf->i = pf->i + 1;
			j = j + 1;
		}
		i = i + 1;
	}
	if (j > 2)
	{
		write(2, "\033[31merror:\033[0m invalid syntax.\n", 32);
		exit(-1);
	}
	return (pf);
}

/*
** Type parsing function.
** While loop goes through type mask and checks for matching
** characters. If a match is found, it is saved to the type.
** Position for substring is marked being next position from
** the saved type character.
*/

t_printf	*parse_type(t_printf *pf)
{
	int i;

	i = 0;
	pf->type = 0;
	while (pf->type_mask[i] != '\0')
	{
		if (pf->type_mask[i] == pf->fmt_copy[pf->i])
			pf->type = pf->type_mask[i];
		i = i + 1;
	}
	if (pf->type == 0)
	{
		write(2, "\033[31merror:\033[0m invalid syntax.\n", 32);
		exit(-1);
	}
	pf->pos = pf->i + 1;
	return (pf);
}
