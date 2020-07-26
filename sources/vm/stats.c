/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stats.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 20:10:50 by jnovotny          #+#    #+#             */
/*   Updated: 2020/07/26 20:12:03 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

size_t	carriage_count(t_car *list)
{
	size_t cnt;

	cnt = 0;
	while (list)
	{
		cnt++;
		list = list->next;
	}
	return (cnt);
}