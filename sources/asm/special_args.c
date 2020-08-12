/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakela <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 15:43:07 by jmakela           #+#    #+#             */
/*   Updated: 2020/07/23 15:43:10 by jmakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** Checks the label by running through the list.
*/

int		check_label(char *label, t_operation **head)
{
	t_operation *cpy;

	cpy = *head;
	check_label_chars(label);
	while (cpy)
	{
		if (cpy->label)
		{
			if (ft_strequ(label, cpy->label))
				return (1);
		}
		cpy = cpy->next;
	}
	return (0);
}

/*
** Determines if arg is special.
** Special args have multiple parts that require math.
** Used in error checking to skip wrong kind of args
*/

int		is_special(char *argum, int func)
{
	int pos;

	pos = 0;
	if (argum[1] == LABEL_CHAR && func)
		return (1);
	else if (argum[0] == LABEL_CHAR && !func)
		return (1);
	else if (func)
		pos = 1;
	if (ft_chrpos(argum, '+') > pos || ft_chrpos(argum, '-') > pos)
		return (1);
	else if (is_hex(argum))
		return (1);
	return (0);
}

void	assign_specials(t_operation *finder, int cnt, int total)
{
	if (finder->arg[cnt][0] == LABEL_CHAR)
		finder->label_pos[cnt] = total;
	else
	{
		free(finder->arg[cnt]);
		if (finder->arg[cnt][0] == DIRECT_CHAR)
			finder->arg[cnt] = ft_strjoin("%", ft_ultoa(total));
		else
			finder->arg[cnt] = ft_ultoa(total);
	}
}

void	special_arg_finder(t_operation **head)
{
	t_operation	*finder;
	int			cnt;
	int			pos;
	int			total;

	finder = *head;
	while (finder)
	{
		cnt = 0;
		while (finder->arg[cnt] && cnt < 3)
		{
			(finder->arg[cnt][0] == DIRECT_CHAR) ? (pos = 1) :
			(pos = 0);
			if ((ft_chrpos(finder->arg[cnt], '+') > pos) ||
				(ft_chrpos(finder->arg[cnt], '-') > pos))
			{
				total = arg_math(head, finder, finder->arg[cnt]);
				assign_specials(finder, cnt, total);
			}
			cnt += 1;
		}
		finder = finder->next;
	}
}

/*
** Attempts to find special args by finding - and + chars.
** Calls checking for special arg if one is identified.
*/

void	match_labels(t_operation **head, int cnt, int pos, int test)
{
	t_operation *finder;

	finder = *head;
	while (finder)
	{
		cnt = 0;
		while (finder->arg[cnt] && cnt < 3)
		{
			(finder->arg[cnt][0] == DIRECT_CHAR) ? (pos = 1) :
			(pos = 0);
			if (ft_chrpos(finder->arg[cnt], '+') > pos ||
				ft_chrpos(finder->arg[cnt], '-') > pos)
				test = special_arg_check(finder->arg[cnt], head);
			else
			{
				if (finder->arg[cnt][pos] == LABEL_CHAR)
					test = check_label(finder->arg[cnt] + pos + 1, head);
			}
			if (!test)
				ft_error("Argument error");
			cnt += 1;
		}
		finder = finder->next;
	}
}
