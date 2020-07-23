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

int		check_lastline(int source_fd)
{
	char temp[1];

	lseek(source_fd, -1, SEEK_END);
	read(source_fd, &temp, 1);
	if (temp[0] != '\n')
		ft_error_exit("File does not end with newline", 0, 0);
	return (1);
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
