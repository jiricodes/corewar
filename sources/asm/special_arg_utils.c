/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_arg_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakela <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 15:58:24 by jmakela           #+#    #+#             */
/*   Updated: 2020/07/23 15:58:25 by jmakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		verify_label(char *label, t_operation **head, int *i)
{
	char	*temp;
	int		start;

	start = 0;
	if (label[*i] == LABEL_CHAR)
	{
		start = *i + 1;
		while (label[*i] != '+' && label[*i] != '-' && label[*i])
			*i = *i + 1;
		temp = ft_strsub(label, start, *i - start);
		if (!check_label(temp, head))
		{
			free(temp);
			return (0);
		}
		free(temp);
	}
	return (1);
}

int		verify_hex(char *label, int *i)
{
	static char hexmask[] = "0123456789abcdefABCDEF";

	if (label[*i] == '0' && (label[*i + 1] == 'x' || label[*i + 1] == 'X'))
	{
		*i = *i + 2;
		if (label[*i])
		{
			while (ft_chrpos(hexmask, label[*i]) >= 0)
				*i = *i + 1;
			if (label[*i] != '\0' && label[*i] != '+' && label[*i] != '-')
				return (0);
		}
		else
			return (0);
	}
	return (1);
}

int		verify_digit(char *label, int *i)
{
	if (ft_isdigit(label[*i]))
	{
		while (ft_isdigit(label[*i]))
			*i = *i + 1;
		if (label[*i] != '\0' && label[*i] != '+' && label[*i] != '-')
			return (0);
	}
	return (1);
}

/*
** Checks if argument has format such as: :live -:l1 + 5 - 0xff
** Splits the arg into chunks and calls checks.
*/

int		special_arg_check(char *label, t_operation **head)
{
	int i;

	i = 0;
	if (label[0] == DIRECT_CHAR)
		i = 1;
	while (label[i])
	{
		if (!verify_label(label, head, &i))
			return (0);
		else if (!verify_hex(label, &i))
			return (0);
		else if (!verify_digit(label, &i))
			return (0);
		if (label[i] == '-' || label[i] == '+')
			i = i + 1;
		else if (label[i] != '\0')
			return (0);
		if (label[i] == '-' || label[i] == '+')
			ft_error("Multiple -/+ in math arg");
	}
	return (1);
}
