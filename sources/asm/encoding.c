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
void	find_position(t_operation **list, t_operation *temp, char *arg, int i)
{
	t_operation *find;

	find = *list;
	while (find)
	{
		if (ft_strequ(find->label, arg))
		{
			temp->label_pos[i] = (find->position - temp->position);
			break ;
		}
		find = find->next;
	}
	if (!find)
	{
		//issue with special labels (example: :l1+1 in Backward.s, l1 is the label but
		//the argument tells it to move +1 further from label positrion.)
		ft_printf("special label, needs fixing = %s\n", arg);
		ft_error_exit("Label not found!\n", 0, 0);
	}
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
				//had some issue with strchr, so I wrote char position finder helper function
				if ((pos = ft_chrpos(temp->arg[i], LABEL_CHAR)) >= 0)
				{
					//still need to deal with labels with increments (leeloo.s, st1+1)
					find_position(list, temp, temp->arg[i] + pos + 1, i);
				}
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
	cnt = ft_strlen(temp) - 1;
	while (cnt > 0 && ft_isspace(temp[cnt]))
		cnt -= 1;
	ret = ft_strncpy(ft_strnew(cnt), temp, cnt);
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

	while (line[cnt] != '\"')
	{
		if (line[cnt] == '\0')
			ft_error_exit("No name or comment present", 0, 0);
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
	ret = remove_trailing_spaces(ret);
	return (ret);
}

// trying to read name and comment using gnl
//now takes t_operation as argument for analysis

void	read_file(t_asm *core, int source_fd, t_operation **list)
{
	char	*line;
	int		total;

	total = 0;
	while (get_next_line(source_fd, &line) > 0)
	{
		// only .name & .comment allowed. others .(...) should be marked as error
		if (ft_strnstr(line, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)))
			core->champ_name = save_name_comment(NAME_CMD_STRING, source_fd, line);
		else if (ft_strnstr(line, COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING)))
			core->champ_comment = save_name_comment(COMMENT_CMD_STRING, source_fd, line);
		else if (ft_strnstr(line, ".extend", ft_strlen(".extend")))
			continue ;
		else
			total = analysis(core, line, list, total);
		free(line);
	}
	while (1)
	{}
	core->byte_size = total;
	// find_labels(list);
}
