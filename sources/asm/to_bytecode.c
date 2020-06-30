/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_bytecode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolopov <asolopov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 12:05:11 by asolopov          #+#    #+#             */
/*   Updated: 2020/06/30 21:13:55 by asolopov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <stdio.h>

void	write_champion(t_asm *core, t_operation *op)
{
	write_headers(core);
	write_exec_code(core, op);
}