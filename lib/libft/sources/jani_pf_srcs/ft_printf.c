/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakela <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 18:22:26 by jmakela           #+#    #+#             */
/*   Updated: 2020/06/24 13:35:28 by jmakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Body of the basic version of printf.
** Some error checking first, if there is only single %, we do nothing.
** If there is no % anywhere in the string, we simply count the length
** and print it out. If there is format string to work with, we make a
** copy of it and start variable arguments, va_list is in our struct pf.
** Call parser to deal with the format string and then end va.
** Finally write the formatted string out, free the string and free pf.
** Returns total number of characters written.
*/

int		ft_printf(const char *format, ...)
{
	t_printf	*pf;

	check_help(format);
	if (ft_strlen(format) == 1 && format[0] == '%')
		return (0);
	if (!(pf = (t_printf*)malloc(sizeof(t_printf))))
		return (-1);
	if (!(ft_strchr(format, '%')))
	{
		pf->total = ft_strlen(format);
		write(1, format, pf->total);
		free(pf);
		return (pf->total);
	}
	if (format)
	{
		pf->fmt_copy = (char*)format;
		va_start(pf->args, format);
		parser(pf);
		va_end(pf->args);
	}
	write(1, pf->final, pf->total);
	free(pf->final);
	free(pf);
	return (pf->total);
}

/*
** Dprintf is a version of printf that works with multiple fds.
** Otherwise exactly the same as the first one, but takes fd
** as an argument before the format string. Writing of formatted
** string is done to the fd provided.
*/

int		ft_dprintf(int fd, const char *format, ...)
{
	t_printf	*pf;

	check_help(format);
	if (ft_strlen(format) == 1 && format[0] == '%')
		return (0);
	if (!(pf = (t_printf*)malloc(sizeof(t_printf))))
		return (-1);
	if (!(ft_strchr(format, '%')))
	{
		pf->total = ft_strlen(format);
		write(fd, format, pf->total);
		free(pf);
		return (pf->total);
	}
	if (format)
	{
		pf->fmt_copy = (char*)format;
		va_start(pf->args, format);
		parser(pf);
		va_end(pf->args);
	}
	write(fd, pf->final, pf->total);
	free(pf->final);
	free(pf);
	return (pf->total);
}

/*
** Sprintf is a version of the printf that writes to a buffer
** the format string that was created, instead of writing it
** out. It should be noted that the buffer string should be
** large enough to receive the formatted string, otherwise
** behaviour is undefined.
*/

int		ft_sprintf(char *buffer, const char *format, ...)
{
	t_printf	*pf;

	check_help(format);
	if (ft_strlen(format) == 1 && format[0] == '%')
		return (0);
	if (!(pf = (t_printf*)malloc(sizeof(t_printf))))
		return (-1);
	if (!(ft_strchr(format, '%')))
	{
		pf->total = ft_strlen(format);
		buffer = ft_strcpy(buffer, format);
		free(pf);
		return (pf->total);
	}
	if (format)
	{
		pf->fmt_copy = (char*)format;
		va_start(pf->args, format);
		parser(pf);
		va_end(pf->args);
	}
	buffer = pf_strcpy(buffer, pf->final, pf->total);
	free(pf->final);
	free(pf);
	return (pf->total);
}
