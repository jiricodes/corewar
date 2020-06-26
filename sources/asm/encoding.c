/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encoding.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolopov <asolopov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 16:10:02 by asolopov          #+#    #+#             */
/*   Updated: 2020/06/25 12:12:34 by asolopov         ###   ########.fr       */
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
		ft_error_exit("Label not found!\n", 0, 0);
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
				if (pos = ft_chrpos(temp->arg[i], LABEL_CHAR) >= 0)
					find_position(list, temp, temp->arg[i] + pos + 1, i);
				i = i + 1;
			}
		}
		temp = temp->next;
	}
}


// a function to extract name & comment from the file using gnl

char	*save_champ_head(char *target, int source_fd, char *line)
{
	char	*ret;
	int		cnt;
	int		pos_start;
	char	*cntd;

	pos_start = 0;
	cnt = ft_strlen(target);
	while (line[cnt] != '\0' && line[cnt] != '\"')
		cnt += 1;
	cnt += 1;
	pos_start = cnt;
	while (line[cnt] != '\0' && line[cnt] != '\"')
		cnt += 1;
	if (line[cnt] == '\0')
	{
		ret = &line[pos_start];
		while(get_next_line(source_fd, &cntd) > 0)
		{
			if (ft_strchr(cntd, '\"'))
			{
				ret = ft_strjoin(ret, "\n"); // need to write memory-friendly function not to have leaks
				ret = ft_strjoin(ret, cntd);
				break ;
			}
			else if (!ft_strchr(cntd, '\"'))
			{
				ret = ft_strjoin(ret, "\n");
				ret = ft_strjoin(ret, cntd);
			}
		}
	}
	else if (line[cnt] == '\"')
		ret = &line[pos_start];
	ret = ft_strsub(ret, 0, ft_strlen(ret) - 1); // there has to be another way to remove last quote marks, cause assembly language can have spaces all around
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
		
		// only .name & .comment allowed. others .(...) should be marked as error
		if (ft_strnstr(line, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING))) // flag breaks this
		{
			core->champ_name = save_champ_head(NAME_CMD_STRING, source_fd, line);
			core->flag = 1;
		}
		else if (core->flag < 10 && ft_strnstr(line, COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING)))
		{
			core->champ_comment = save_champ_head(COMMENT_CMD_STRING, source_fd, line);
			core->flag = 10;
		}
		else if (core->flag >= 10)
			total = analysis(core, line, list, total);
		free(line);
	
	core->byte_size = total;
	find_labels(list);
}