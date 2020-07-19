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
				ft_dprintf(2, "argument error on line %d\n", core->line_cnt);
				ft_error_exit("check_argument error", 0, 0);
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
int			save_label_op(t_operation **list, t_operation *new, char *line, int *i)
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
** based on separators and labels chars, finds the positions of labels and operation
** creates new links if there are multiple labels
** calls get_args to finalize the link and check_operation to make sure link has no errors
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

/*
** Reformatting removes all whitespace and replaces it with separator chars as needed.
** Skips comments and copies all chars that are not space/tab while skipping spaces.
** Special cases are space after label, which is replaced by separator to make things easier
** and space after operation, which too is replaced by separator.
*/

char		*reduce_whitespace(char *line, char *reformed, int *i, int *pos)
{
	while (line[*i])
	{
		if (line[*i] == COMMENT_CHAR || line[*i] == ALT_COMMENT_CHAR)
		{
			line[*i] = '\0';
			break ;
		}
		if (line[*i] != ' ' && line[*i] != '\t')
		{
			reformed[*pos] = line[*i];
			*pos += 1;
		}
		else
		{
			reformed[*pos] = ' ';
			*pos += 1;
			while (line[*i] == ' ' || line[*i] == '\t')
				*i += 1;
			*i -= 1;
		}
		*i += 1;
	}
	if (reformed[*pos - 1] == ' ')
		*pos -= 1;
	return (reformed);
}

/*
** Final reformat of reformed string.
** After reduce whitespace, only important stuff is left and
** it is copied to final string.
*/
char		*final_reformat(char *reformed, int *i, int *pos, int separator)
{
	char	*final;

	if (!(final = (char*)malloc(sizeof(char) * ft_strlen(reformed) + 2)))
		ft_error_exit("Malloc error", 0, 0);
	while (reformed[*pos])
	{
		if (reformed[*pos] != ' ')
		{
			final[*i] = reformed[*pos];
			*i += 1;
		}
		else if (reformed[*pos] == ' ' && !separator)
		{
			(reformed[*pos - 1] == LABEL_CHAR) ? (final[*i] = SEPARATOR_CHAR) : 0;
			if (ft_isalpha(reformed[*pos - 1]) && !separator)
			{
				final[*i] = SEPARATOR_CHAR;
				separator = 1;
			}
			*i += 1;
		}
		*pos += 1;
	}
	ft_strdel(&reformed);
	return (final);
}

/*
** Calls reformatting functions.
*/
char		*reformat(char *line)
{
	int		i;
	int		pos;
	char	*reformed;

	i = 0;
	pos = 0;
	if (!(reformed = (char*)malloc(sizeof(char) * ft_strlen(line) + 2)))
		ft_error_exit("Malloc error", 0, 0);
	reformed = reduce_whitespace(line, reformed, &i, &pos);
	reformed[pos] = '\0';
	pos = 0;
	i = 0;
	reformed = final_reformat(reformed, &i, &pos, 0);
	reformed[i] = SEPARATOR_CHAR;
	reformed[i + 1] = '\0';
	return (reformed);
}

/*
** Parser.
** Error checks the line a little bit at first and ignores comments and .stuff.
** Calls reformat to alter the line, then makes new link and gets labels and operations.
*/

int			lex_parser(t_asm *core, t_operation **list, char *line)
{
	char	*reformed;

	if (!line || line[0] == '\0')
		return (0);
	while (*line == ' ' || *line == '\t')
		line = line + 1;
	if (*line == '\0')
		return (0);
	if (*line == COMMENT_CHAR || *line == ALT_COMMENT_CHAR || *line == '.')
		return (1);
	reformed = reformat(line);
	list_append(list);
	get_label_op(core, list, reformed);
	return (1);
}
