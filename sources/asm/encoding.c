/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encoding.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolopov <asolopov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 16:10:02 by asolopov          #+#    #+#             */
/*   Updated: 2020/06/08 23:24:41 by asolopov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

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
				ret = ft_strcat(ret, "\n"); // need to write memory-friendly function not to have leaks
				ret = ft_strcat(ret, cntd);
				break ;
			}
			else if (!ft_strchr(cntd, '\"'))
			{
				ret = ft_strcat(ret, "\n");
				ret = ft_strcat(ret, cntd);
			}
		}
	}
	else if (line[cnt] == '\"')
		ret = &line[pos_start];
	ret = ft_strsub(ret, 0, ft_strlen(ret) - 1); // there has to be another way to remove last quote marks, cause assembly language can have spaces all around
	return (ret);
}

// trying to read name and comment using gnl

void	read_file(t_asm *core, int source_fd)
{
	char	*line;

	while (get_next_line(source_fd, &line) > 0)
		
		// only .name & .comment allowed. others .(...) should be marked as error
		if (ft_strnstr(line, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)))
			core->champ_name = save_champ_head(NAME_CMD_STRING, source_fd, line);
		else if (ft_strnstr(line, COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING)))
			core->champ_comment = save_champ_head(COMMENT_CMD_STRING, source_fd, line);
		free(line);
	printf("%s\n", core->champ_name);
	printf("%s\n", core->champ_comment);
}