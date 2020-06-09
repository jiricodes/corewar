/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chaps.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 10:48:05 by jnovotny          #+#    #+#             */
/*   Updated: 2020/06/09 11:01:30 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_champ		*init_champ(char	*filename)
{
	t_champ		*champ;

	if (!ft_strendwith(filename, ".cor"))
	{
		ft_printf("Incorrect file type: %s\n", filename);
		ft_error_exit("Must be .cor type. Terminating", NULL, NULL);
	}
	champ = (t_champ*)ft_memalloc(sizeof(t_champ));
	if (!champ)
		ft_error_exit("Malloc at init_champ", NULL, NULL);
}