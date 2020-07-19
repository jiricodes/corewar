/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encoding.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolopov <asolopov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 16:10:02 by asolopov          #+#    #+#             */
/*   Updated: 2020/07/01 13:37:38 by asolopov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

//When label is found in argument, goes through the list again to find the position
//where argument label is pointing to and calculates how many bytes you must go
//forwards or backwards, if the label is not found at all calls error exit
int	find_position(t_operation **list, t_operation *temp, char *arg)
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



//goes through the linked list attempting to find labels in arguments
void	find_labels(t_operation **list)
{
	t_operation *temp;
	int i;
	int pos;

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
						temp->label_pos[i] = find_position(list, temp, temp->arg[i] + pos + 1);
				i = i + 1;
			}
		}
		temp = temp->next;
	}
}

char	*strjoin_first(char *s1, char *s2)
{
	char	*temp;
	char	*ret;

	temp = ft_strdup(s1);
	free(s1);
	ret = ft_strjoin(temp, s2);
	free(temp);
	return (ret);
}

char	*continue_reading(int source_fd)
{
	char	*line;
	char	*ret;

	ret = ft_strnew(10);
	while(get_next_line(source_fd, &line) > 0)
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

char	*remove_trailing_spaces(char *src)
{
	int		cnt;
	char	*temp;
	char	*ret;

	temp = ft_strdup(src);
	free(src);
	cnt = 0;
	while (temp[cnt] != '\"')
		cnt += 1;
	ret = ft_strncpy(ft_strnew(cnt), temp, cnt);
	cnt += 1;
	while (temp[cnt] != '\0')
	{
		if (!ft_isspace(temp[cnt]))
		{
			if (temp[cnt] == COMMENT_CHAR || temp[cnt] == ALT_COMMENT_CHAR)
				break ;
			else
				ft_error_exit("Invalid char following name/comment", 0, 0);
		}
		cnt += 1;
	}
	free(temp);
	return (ret);
}
// a function to extract name & comment from the file using gnl
char	*save_name_comment(char *target, int source_fd, char *line)
{
	char	*ret;
	int		cnt;
	int		pos_start;
	char	*cntd;

	cnt = 0;
	while (line[cnt] != '\"')
	{
		(line[cnt] == '\0') ? ft_error_exit("No name or comment present", 0, 0) : 0;
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
	else if (line[cnt] == '\"')
		ret = ft_strdup(&line[pos_start]);
	return (remove_trailing_spaces(ret));
}

int		check_lastline(int source_fd)
{
	char temp[1];

	lseek(source_fd, -1, SEEK_END);
	read(source_fd, &temp, 1);
	if (temp[0] != '\n')
		ft_error_exit("File does not end with newline", 0, 0);
	return (1);
}

//removed the part that continued after .extend and made lex_parser to
//ignore lines .(insert_text) there were also stuff like .code etc
//now calls special arg finder to deal with special arguments
void	read_file(t_asm *core, int source_fd, t_operation **list)
{
	char	*line;

	while (get_next_line(source_fd, &line) > 0)
	{
		core->line_cnt += 1;
		if (ft_strnstr(line, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)))
			core->champ_name = save_name_comment(NAME_CMD_STRING, source_fd, line);
		else if (ft_strnstr(line, COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING)))
			core->champ_comment = save_name_comment(COMMENT_CMD_STRING, source_fd, line);
		else
			lex_parser(core, list, line);
		free(line);
	}
	check_lastline(source_fd);
	match_labels(list, 0, 0, 1);
	get_size_type(list, core);
	find_labels(list);
	special_arg_finder(list);
}
