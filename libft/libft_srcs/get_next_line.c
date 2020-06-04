/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 09:47:46 by jnovotny          #+#    #+#             */
/*   Updated: 2019/11/26 14:52:28 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*assign_str(char **stack, const int fd)
{
	int		i;
	char	*res;
	char	*extr;

	i = 0;
	while (stack[fd][i] != '\n' && stack[fd][i] != '\0')
		i = i + 1;
	if (stack[fd][i] == '\n')
	{
		res = ft_strsub(stack[fd], 0, i);
		extr = ft_strsub(stack[fd], i + 1, ft_strlen(stack[fd]) - (i + 1));
		free(stack[fd]);
		stack[fd] = extr;
	}
	else
	{
		res = ft_strdup(stack[fd]);
		ft_strdel(&stack[fd]);
	}
	return (res);
}

int		get_next_line(const int fd, char **line)
{
	static char	*stack[MAX_FD];
	char		buf[BUFF_SIZE + 1];
	int			ret;
	char		*temp;

	if (fd < 0 || fd > MAX_FD || !line)
		return (-1);
	while (0 < (ret = read(fd, buf, BUFF_SIZE)))
	{
		buf[ret] = '\0';
		if (stack[fd] == NULL)
			stack[fd] = ft_strnew(1);
		temp = ft_strjoin(stack[fd], buf);
		free(stack[fd]);
		stack[fd] = temp;
		if (ft_strchr(buf, 10))
			break ;
	}
	if (ret == -1)
		return (ret);
	if (ret == 0 && (stack[fd] == NULL || stack[fd][0] == '\0'))
		return (ret);
	if ((*line = assign_str(stack, fd)))
		return (1);
	return (0);
}
