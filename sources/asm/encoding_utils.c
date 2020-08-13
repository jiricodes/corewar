/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encoding_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolopov <asolopov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 15:55:03 by jmakela           #+#    #+#             */
/*   Updated: 2020/07/29 14:37:20 by asolopov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

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

void	check_label_chars(char *label, int line)
{
	int i;

	i = 0;
	while (label[i])
	{
		if (!ft_strchr(LABEL_CHARS, label[i]))
		{
			ft_dprintf(2, "Invalid label: \"%s\" on line %d\n", label, line);
			ft_error("Wrong chars in label!");
		}
		i += 1;
	}
}

void	check_lastline(int source_fd)
{
	char	temp[1];
	char	*last;
	int		i;

	i = -2;
	lseek(source_fd, -1, SEEK_END);
	read(source_fd, &temp, 1);
	while (temp[0] != '\n')
	{
		lseek(source_fd, i, SEEK_END);
		read(source_fd, &temp, 1);
		i -= 1;
	}
	i = (i + 2) * -1;
	if (!(last = (char*)malloc(sizeof(char) * i + 1)))
		ft_error("Malloc error");
	read(source_fd, last, i);
	last[i] = '\0';
	i = 0;
	while (last[i] == ' ' || last[i] == '\t')
		i += 1;
	if (last[i] != '\0' && last[i] != COMMENT_CHAR &&
		last[i] != ALT_COMMENT_CHAR)
		ft_error("File does not end with newline!");
	free(last);
}

void	do_checks(t_asm *core, t_operation **list)
{
	if (core->champ_name == NULL)
		ft_error("Champ name is missing!");
	if (core->champ_comment == NULL)
		ft_error("Champ comment is missing!");
	if (ft_strlen(core->champ_name) > PROG_NAME_LENGTH)
		ft_error("Champ name is too long (128)");
	if (ft_strlen(core->champ_comment) > COMMENT_LENGTH)
		ft_error("Champ comment is too long (2048)");
	check_lastline(core->source_fd);
	match_labels(list, 0, 0, 1);
	get_size_type(list, core);
	find_labels(list);
	special_arg_finder(list);
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
				ft_error("Invalid char following name/comment!");
		}
		cnt += 1;
	}
	free(temp);
	return (ret);
}
