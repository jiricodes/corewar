/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakela <jmakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 20:22:38 by jmakela           #+#    #+#             */
/*   Updated: 2020/08/06 14:46:28 by jmakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_error.h"

void	ft_error(char *user_msg)
{
	if (errno != 0)
		perror("SYSTEM ERROR MESSAGE: ");
	if (user_msg)
		ft_dprintf(2, "%{RED}%{BOLD}USER ERROR MESSAGE%{EOC}: %s\n", user_msg);
	exit(-1);
}
