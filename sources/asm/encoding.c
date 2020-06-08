/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encoding.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolopov <asolopov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 16:10:02 by asolopov          #+#    #+#             */
/*   Updated: 2020/06/08 19:00:44 by asolopov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

// small function to copy extracted part to a new string

char	*ft_strndup(const char *s1, size_t len)
{
	char	*cpy;
	int		i;
	int		l;

	i = 0;
	l = len;
	cpy = (char*)malloc(sizeof(char) * (l + 1));
	if (cpy == NULL)
		return (NULL);
	while (i < l)
	{
		cpy[i] = s1[i];
		i = i + 1;
	}
	cpy[i] = '\0';
	return (cpy);
}

// checking for length and chars

void	check_string(char *str, char *type)
{
	if (ft_strcmp(type, "name"))
	{
		if (ft_strchr(str, '\"'))
			exit(0);
		if (ft_strlen(str) > PROG_NAME_LENGTH)
		{
			exit(0);
		}
	}
	else if (ft_strcmp(type, "comment"))
	{
		if (ft_strchr(str, '\"'))
			exit(0);
		if (ft_strlen(str) > COMMENT_LENGTH)
			exit(0);
	}
}

// extracting champs name from line

void	save_champ_name(int source_fd, t_asm *core, char *line)
{
	char	*ret;
	int		cnt;
	int		pos_start;
	char	*cntd;

	pos_start = 0;
	cnt = ft_strlen(NAME_CMD_STRING);
	// while (1)
	// {
	while (line[cnt] != '\"')
		cnt += 1;
	pos_start = cnt;
	cnt += 1;
	while (line[cnt] != '\0' && line[cnt] != '\"')
		cnt += 1;
	if (line[cnt] == '\0')
	{
		ret = &line[pos_start];
		while(get_next_line(source_fd, &cntd) > 0)
		{
			if (ft_strchr(cntd, '\"'))
			{
				ret = ft_strcat(ret, "\n");
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
	printf("%s\n", ret);
}

// extracting champs comment from line

void	save_champ_comment(t_asm *core, char *line)
{
	int x;
	int y;
	char *new;

	x = ft_strlen(COMMENT_CMD_STRING);
	y = ft_strlen(line);
	while (line[x] != '\"')
	{
		if (line[x] == '\0')
			exit(0);
		x += 1;
	}
	while (line[y] != '\"')
	{
		if (y <= ft_strlen(COMMENT_CMD_STRING))
			exit(0);
		y -= 1;
	}
	if (y <= x)
		exit(0);
	new = ft_strndup(line + 1 + x, y - x - 1);
	check_string(new, "comment");
	core->champ_comment = new;	
}

// trying to read name and comment using gnl

void	read_file(t_asm *core, int source_fd)
{
	char	*line;

	while (get_next_line(source_fd, &line) > 0)
		
		if (ft_strnstr(line, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)))
			save_champ_name(source_fd, core, line);
		// else if (ft_strnstr(line, COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING)))
		// 	save_champ_comment(core, line);
		free(line);
	// printf("%s\n", core->champ_name);
	// printf("%s\n", core->champ_comment);
}