/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_math.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakela <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 18:20:12 by jmakela           #+#    #+#             */
/*   Updated: 2020/08/12 18:20:17 by jmakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** If argument has been identified as hex,
** get_hex calls functions to change it to base 10.
*/

void		get_hex(t_operation *new, char *line, int cnt)
{
	char	*temp;
	char	*hex;

	temp = x_to_deci(line);
	hex = ft_strjoin("%", temp);
	new->arg[cnt] = ft_strdup(hex);
	free(temp);
	free(hex);
}
