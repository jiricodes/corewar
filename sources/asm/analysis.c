/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analysis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 17:45:58 by jnovotny          #+#    #+#             */
/*   Updated: 2020/07/14 17:53:24 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** extracts arguments from reformatted string
** using separator char arguments are found and copied
** if hex is found, it is converted to decimal string
*/

void get_args(t_asm *core, t_operation *new, char *line)
{
	int i;
	int cnt;
	char *hex;
	char *temp;

	i = 0;
	cnt = 0;
	while (line[i])
	{
		if (line[i] == SEPARATOR_CHAR)
		{
			if (cnt > 2)
			{
				ft_printf("Too many instructions on row: %d\n", core->line_cnt);
				ft_error_exit("check_argument error", 0, 0);
			}
			line[i] = '\0';
			if (is_hex(line))
			{
				temp = x_to_deci(line);
				hex = put_percent(temp);
				new->arg[cnt] = ft_strdup(hex);
				free(temp);
				free(hex);
			}
			else
				new->arg[cnt] = ft_strdup(line);
			line = line + i + 1;
			i = 0;
			cnt = cnt + 1;
		}
		if (line[i] != '\0')
			i = i + 1;
	}
}

/*
** extracts possible labels and operation from reformatted string
** based on separators and labels chars, finds the positions of labels and operation
** creates new links if there are multiple labels
** calls get_args to finalize the link and check_operation to make sure link has no errors
*/

void get_label_op(t_asm *core, t_operation **list, char *line)
{
	int i;
	int pos;
	t_operation *new;

	i = 0;
	new = *list;
	while (new->next)
		new = new->next;
	while (line[i])
	{
		if (line[i] == SEPARATOR_CHAR && line[i - 1] == LABEL_CHAR)
		{
			line[i - 1] = '\0';
			if (new->label != NULL)
			{
				list_append(list);
				new = new->next;
			}
			new->label = ft_strdup(line);
			line = line + i + 1;
			i = 0;
		}
		else if (line[i] == SEPARATOR_CHAR && line[i - 1] != LABEL_CHAR)
		{
			line[i] = '\0';
			new->op_name = ft_strdup(line);
			line = line + i + 1;
			break;
		}
		if (line[i] != '\0')
			i = i + 1;
	}
	if (new->op_name)
	{
		get_args(core, new, line);
		check_operation(new, core);
	}
}

/*
** reformat removes all whitespace and replaces it with separator chars as needed
** skips comments, copies all chars that are not space/tab and skips spaces
** special cases are space after label, which is replaced by separator to make things easier
** and space after operation, which too is replaced by separator
*/

char *reformat(char *line)
{
	int i;
	int pos;
	char *reformat;
	char *copy;
	int comma;

	i = 0;
	pos = 0;
	comma = 0;
	copy = (char*)malloc(sizeof(char) * ft_strlen(line) + 2);
	while (line[i])
	{
		if (line[i] == COMMENT_CHAR || line[i] == ALT_COMMENT_CHAR)
			break ;
		else if (line[i] != ' ' && line[i] != '\t')
		{
			copy[pos] = line[i];
			pos = pos + 1;
		}
		else 
		{
			if (line[i - 1] == LABEL_CHAR || (ft_isalpha(line[i - 1]) && !comma))
			{
				if (ft_isalpha(line[i - 1]))
					comma = 1;
				copy[pos] = SEPARATOR_CHAR;
				pos = pos + 1;
			}
			while (line[i] == ' ' || line[i] == '\t')
				i = i + 1;
			i = i - 1;
		}
		i = i + 1;
	}
	copy[pos] = SEPARATOR_CHAR;
	copy[pos + 1] = '\0';
	reformat = (char*)realloc(copy, sizeof(char) * pos + 2);
	return (reformat);
}

/*
** new parser
** error checks the line a little bit at first and ignores comments and .stuff
** calls reformat to alter the line, then makes new link and gets labels and operations
*/

int lex_parser(t_asm *core, t_operation **list, char *line)
{
	char *reformed;

	if (!line || line[0] == '\0' || line[0] == '\n')
		return (0);
	while (*line == ' ' || *line == '\t' || *line == '\n')
		line = line + 1;
	if (*line == '\0' || *line == COMMENT_CHAR || *line == ALT_COMMENT_CHAR || *line == '.')
		return (0);
	reformed = reformat(line);
	list_append(list);
	get_label_op(core, list, reformed);
	return (1);
}
