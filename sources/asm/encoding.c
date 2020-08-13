/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encoding.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 16:10:02 by asolopov          #+#    #+#             */
/*   Updated: 2020/08/12 16:05:42 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** When label found, go through list to find the position it's pointing to.
** Calculate how many bytes to move forward/backward, if not found, error.
*/

int		find_position(t_operation **list, t_operation *temp, char *arg)
{
	t_operation *find;

	find = *list;
	while (find)
	{
		if (ft_strequ(find->label, arg))
			return (find->position - temp->position);
		find = find->next;
	}
	return (0);
}

/*
** Go through the linked list to find labels
*/

void	find_labels(t_operation **list)
{
	t_operation	*temp;
	int			i;
	int			pos;

	temp = *list;
	while (temp)
	{
		i = 0;
		pos = 0;
		if (temp->op_name)
		{
			while (temp->arg[i] && i < 3)
			{
				if ((pos = ft_chrpos(temp->arg[i], LABEL_CHAR)) >= 0)
					temp->label_pos[i] = find_position(list, temp, \
					temp->arg[i] + pos + 1);
				i = i + 1;
			}
		}
		temp = temp->next;
	}
}

char	*continue_reading(int source_fd)
{
	char	*line;
	char	*ret;

	ret = ft_strnew(10);
	while (get_next_line(source_fd, &line) > 0)
	{
		if (ft_strchr(line, '\"'))
		{
			ret = strjoin_first(ret, "\n");
			ret = strjoin_first(ret, line);
			free(line);
			break ;
		}
		else if (!ft_strchr(line, '\"'))
		{
			ret = strjoin_first(ret, "\n");
			ret = strjoin_first(ret, line);
		}
		free(line);
	}
	return (ret);
}

/*
** Extract name and comment using gnl
*/

char	*save_name_comment(int source_fd, char *line)
{
	char	*ret;
	int		cnt;
	int		pos_start;
	char	*cntd;

	cnt = 0;
	while (line[cnt] != '\"')
	{
		(line[cnt] == '\0') ? ft_error("No name or comment!") : 0;
		cnt += 1;
	}
	pos_start = cnt + 1;
	cnt += 1;
	while (line[cnt] != '\0' && line[cnt] != '\"')
		cnt += 1;
	if (line[cnt] == '\0')
	{
		ret = ft_strdup(&line[pos_start]);
		cntd = continue_reading(source_fd);
		ret = strjoin_first(ret, cntd);
		free(cntd);
	}
	else
		ret = ft_strdup(&line[pos_start]);
	return (remove_trailing_spaces(ret));
}

/*
** Uses gnl to read the file. Calls funcs to extract name/comment and
** parser to reformat and check lines. Then calls matching of labels,
** getting of size and type of op and args, finds labels and checks
** for special args
*/

void	read_file(t_asm *core, int source_fd, t_operation **list)
{
	char	*line;
	char	*tmp;

	while (get_next_line(source_fd, &line) > 0)
	{
		tmp = line;
		core->line_cnt += 1;
		while ((*tmp == ' ' || *tmp == '\t') && *tmp != '\0')
			tmp++;
		if (ft_strnstr(tmp, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)))
		{
			(core->champ_name) ? ft_error("Multiple names!") : 0;
			core->champ_name = save_name_comment(source_fd, line);
		}
		else if (ft_strnstr(tmp, COMMENT_CMD_STRING, \
							ft_strlen(COMMENT_CMD_STRING)))
		{
			(core->champ_comment) ? ft_error("Multiple comments!") : 0;
			core->champ_comment = save_name_comment(source_fd, line);
		}
		else
			lex_parser(core, list, line);
		free(line);
	}
	do_checks(core, list);
}
