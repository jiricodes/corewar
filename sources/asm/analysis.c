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
** Removes all whitespace and replaces it with separator chars as needed.
** Skips comments and copies all not space/tab chars while skipping spaces.
** Special cases are space after label, which is replaced by separator
** and space after operation, which too is replaced by separator.
*/

char		*reduce_whitespace(char *line, char *reform, int *i, int *pos)
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
			if ((line[*i] == DIRECT_CHAR || line[*i] == '-') && line[*i - 1] != ' ' && line[*i - 1] != '\t' && line[*i - 1] != SEPARATOR_CHAR)
			{
				reform[*pos] = ' ';
				*pos += 1;
			}
			reform[*pos] = line[*i];
			*pos += 1;
		}
		else
		{
			reform[*pos] = ' ';
			*pos += 1;
			while (line[*i] == ' ' || line[*i] == '\t')
				*i += 1;
			*i -= 1;
		}
		*i += 1;
	}
	if (reform[*pos - 1] == ' ')
		*pos -= 1;
	return (reform);
}

/*
** Final reformat of reform string.
** After reduce whitespace, only important stuff is left and
** it is copied to final string.
*/

char		*final_reformat(char *reform, int *i, int *pos, int separator)
{
	char	*final;

	if (!(final = (char*)malloc(sizeof(char) * ft_strlen(reform) + 2)))
		ft_error("Malloc error");
	while (reform[*pos])
	{
		if (reform[*pos] != ' ')
		{
			final[*i] = reform[*pos];
			*i += 1;
		}
		else if (reform[*pos] == ' ' && !separator)
		{
			(reform[*pos - 1] == LABEL_CHAR) ? (final[*i] = SEPARATOR_CHAR) : 0;
			if (ft_isalpha(reform[*pos - 1]) && !separator)
			{
				final[*i] = SEPARATOR_CHAR;
				separator = 1;
			}
			*i += 1;
		}
		*pos += 1;
	}
	ft_strdel(&reform);
	return (final);
}

/*
** Calls reformatting functions.
*/

char		*reformat(char *line)
{
	int		i;
	int		pos;
	char	*reform;

	i = 0;
	pos = 0;
	if (!(reform = (char*)malloc(sizeof(char) * ft_strlen(line) + 2)))
		ft_error("Malloc error");
	reform = reduce_whitespace(line, reform, &i, &pos);
	reform[pos] = '\0';
	pos = 0;
	i = 0;
	reform = final_reformat(reform, &i, &pos, 0);
	reform[i] = SEPARATOR_CHAR;
	reform[i + 1] = '\0';
	return (reform);
}

/*
** Parser.
** Error checks the line a little bit at first and ignores comments and .stuff.
** Calls reformat to alter the line, makes new link and gets labels and ops.
*/

int			lex_parser(t_asm *core, t_operation **list, char *line)
{
	char	*reform;

	if (!line || line[0] == '\0')
		return (0);
	while (*line == ' ' || *line == '\t')
		line = line + 1;
	if (*line == '\0')
		return (0);
	if (*line == COMMENT_CHAR || *line == ALT_COMMENT_CHAR)
		return (1);
	//ft_printf("name = %s, comment = %s\n", core->champ_name, core->champ_comment);
	if (!core->champ_name || !core->champ_comment || *line == '.')
	{
		ft_dprintf(2, "Issue on line %d\n", core->line_cnt);
		ft_error("Lexical error");
	}
	reform = reformat(line);
	list_append(list);
	get_label_op(core, list, reform);
	return (1);
}
