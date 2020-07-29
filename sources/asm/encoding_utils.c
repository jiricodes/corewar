/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encoding_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakela <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 15:55:03 by jmakela           #+#    #+#             */
/*   Updated: 2020/07/23 15:55:04 by jmakela          ###   ########.fr       */
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

int		check_name_cmt(t_asm *core)
{
	int i;

	i = 0;
	if (core->champ_name == NULL)
		ft_error_exit("Champ name is missing!", 0, 0);
	if (core->champ_comment == NULL)
		ft_error_exit("Champ comment is missing!", 0, 0);
	if (ft_strlen(core->champ_name) > PROG_NAME_LENGTH)
		ft_error_exit("Champ name is too long (128)", 0, 0);
	if (ft_strlen(core->champ_name) > COMMENT_LENGTH)
		ft_error_exit("Champ comment is too long (2048)", 0, 0);
}

int		check_label_chars(char *label)
{
	int i;

	i = 0;
	while (label[i])
	{
		if (!ft_strchr(LABEL_CHARS, label[i]))
			ft_error_exit("Wrong chars in label!", 0, 0);
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
		ft_error_exit("Malloc error", 0, 0);
	read(source_fd, last, i);
	last[i] = '\0';
	i = 0;
	while (last[i] == ' ' || last[i] == '\t')
		i += 1;
	if (last[i] != '\0' && last[i] != COMMENT_CHAR &&
		last[i] != ALT_COMMENT_CHAR)
		ft_error_exit("File does not end with newline", 0, 0);
	free(last);
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
