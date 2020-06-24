/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakela <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 18:37:11 by jmakela           #+#    #+#             */
/*   Updated: 2020/06/24 13:21:08 by jmakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Background color parsing function.
** In case parse_color didn't find a match for type '{'.
** It string n compares the from the current string
** position n amount of chars to find out if one of
** the color defines matches. Appends the correct
** colorcode to the final string.
*/

static void		parse_b_color(t_printf *pf, char *str)
{
	int i;

	i = 0;
	if ((ft_strncmp(str, "{B_BLACK}", 9) == 0) && (i = 8))
		append_substr(pf, B_BLACK, 5);
	else if ((ft_strncmp(str, "{B_RED}", 7) == 0) && (i = 6))
		append_substr(pf, B_RED, 5);
	else if ((ft_strncmp(str, "{B_GREEN}", 9) == 0) && (i = 8))
		append_substr(pf, B_GREEN, 5);
	else if ((ft_strncmp(str, "{B_YELLOW}", 10) == 0) && (i = 9))
		append_substr(pf, B_YELLOW, 5);
	else if ((ft_strncmp(str, "{B_BLUE}", 8) == 0) && (i = 7))
		append_substr(pf, B_BLUE, 5);
	else if ((ft_strncmp(str, "{B_PURPLE}", 10) == 0) && (i = 9))
		append_substr(pf, B_PURPLE, 5);
	else if ((ft_strncmp(str, "{B_CYAN}", 8) == 0) && (i = 7))
		append_substr(pf, B_CYAN, 5);
	else if ((ft_strncmp(str, "{B_WHITE}", 9) == 0) && (i = 8))
		append_substr(pf, B_WHITE, 5);
	else if ((ft_strncmp(str, "{BOLD}", 6) == 0) && (i = 5))
		append_substr(pf, BOLD, 4);
	else if ((ft_strncmp(str, "{UNDERLINE}", 11) == 0) && (i = 10))
		append_substr(pf, UNDERLINE, 4);
	pf->i = pf->i + i;
}

/*
** Because damn function was too long.
*/

static void		parse_white(t_printf *pf, char *str)
{
	int i;

	i = 0;
	if ((ft_strncmp(str, "{WHITE}", 7) == 0) && (i = 6))
		append_substr(pf, WHITE, 5);
	else
		parse_b_color(pf, str);
	pf->i = pf->i + i;
}

/*
** Color parsing function.
** If type is found to be '{', parse_color is called.
** It string n compares the from the current string
** position n amount of chars to find out if one of
** the color defines matches. Appends the correct
** colorcode to the final string.
*/

t_printf		*parse_color(t_printf *pf, char *str)
{
	int i;

	i = 0;
	if ((ft_strncmp(str, "{EOC}", 5) == 0) && (i = 4))
		append_substr(pf, EOC, 4);
	else if ((ft_strncmp(str, "{BLACK}", 7) == 0) && (i = 6))
		append_substr(pf, BLACK, 5);
	else if ((ft_strncmp(str, "{RED}", 5) == 0) && (i = 4))
		append_substr(pf, RED, 5);
	else if ((ft_strncmp(str, "{GREEN}", 7) == 0) && (i = 6))
		append_substr(pf, GREEN, 5);
	else if ((ft_strncmp(str, "{YELLOW}", 8) == 0) && (i = 7))
		append_substr(pf, YELLOW, 5);
	else if ((ft_strncmp(str, "{BLUE}", 6) == 0) && (i = 5))
		append_substr(pf, BLUE, 5);
	else if ((ft_strncmp(str, "{PURPLE}", 8) == 0) && (i = 7))
		append_substr(pf, PURPLE, 5);
	else if ((ft_strncmp(str, "{CYAN}", 6) == 0) && (i = 5))
		append_substr(pf, CYAN, 5);
	else
		parse_white(pf, str);
	pf->i = pf->i + i;
	pf->pos = pf->i + 1;
	return (pf);
}
