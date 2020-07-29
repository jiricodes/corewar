/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analysis_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolopov <asolopov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 15:48:17 by jmakela           #+#    #+#             */
/*   Updated: 2020/07/29 14:29:23 by asolopov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** If argument has been identified as hex,
** get_hex calls functions to change it to base 10.
*/

void		get_hex(t_operation *new, char *line, int cnt)
{
	char	*temp;
	char	*hex;

	temp = x_to_deci(line);
	hex = ft_strjoin("%", temp);
	new->arg[cnt] = ft_strdup(hex);
	free(temp);
	free(hex);
}

/*
** Extracts arguments from reformatted string.
** Using separator char arguments are found and copied.
** If hex is found, it is converted to decimal string.
*/

void		get_args(t_asm *core, t_operation *new, char *line)
{
	int		i;
	int		cnt;

	i = 0;
	cnt = 0;
	while (line[i])
	{
		if (line[i] == SEPARATOR_CHAR)
		{
			if (cnt > 2)
			{
				ft_dprintf(2, "Argument error on line %d\n", core->line_cnt);
				ft_error_exit("Lexical error", 0, 0);
			}
			line[i] = '\0';
			if (is_hex(line))
				get_hex(new, line, cnt);
			else
				new->arg[cnt] = ft_strdup(line);
			line = line + i + 1;
			cnt += 1;
			i = -1;
		}
		i += 1;
	}
}

/*
** Function to save label or op once SEPARATOR_CHAR has been found.
*/

int			save_label_op(t_operation **list, t_operation *new, \
			char *line, int *i)
{
	if (line[*i] == SEPARATOR_CHAR && line[*i - 1] == LABEL_CHAR)
	{
		line[*i - 1] = '\0';
		if (new->label != NULL)
		{
			list_append(list);
			new = new->next;
		}
		new->label = ft_strdup(line);
		check_label_chars(new->label);
	}
	else if (line[*i] == SEPARATOR_CHAR && line[*i - 1] != LABEL_CHAR)
	{
		line[*i] = '\0';
		new->op_name = ft_strdup(line);
		return (0);
	}
	return (1);
}

/*
** extracts possible labels and operation from reformatted string
** based on separators and labels chars, finds the positions of labels and op
** creates new links if there are multiple labels
** calls get_args to finalize the link and check_operation to make has no errors
*/

void		get_label_op(t_asm *core, t_operation **list, char *line)
{
	int			i;
	int			pos;
	t_operation	*new;

	i = 0;
	new = *list;
	while (new->next)
		new = new->next;
	while (line[i])
	{
		if (line[i] == SEPARATOR_CHAR)
		{
			save_label_op(list, new, line, &i);
			line = line + i + 1;
			i = 0;
			if (new->op_name)
				break ;
		}
		(line[i] != '\0') ? (i += 1) : 0;
	}
	if (new->op_name)
	{
		get_args(core, new, line);
		check_operation(new, core);
	}
}
