/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolopov <asolopov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 20:43:59 by asolopov          #+#    #+#             */
/*   Updated: 2020/06/30 20:51:44 by asolopov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		swap_int16(int val)
{
	return ((val & 0x00FF) << 8 | (val & 0xFF00) >> 8);
}

int		swap_int32(int val)
{
	return ((val & 0xFF000000) >> 24 | (val & 0x00FF0000) >> 8 |
	(val & 0x0000FF00) << 8 | (val & 0x000000FF) << 24);
}

int		get_arg_code(t_operation *operation)
{
	int cnt;
	int shift;
	int	ret;

	cnt = 0;
	shift = 6;
	ret = 0b00000000;
	while (cnt < 3)
	{
		if (operation->argtypes[cnt] == T_REG)
			ret += T_REG_CODE << shift;
		else if (operation->argtypes[cnt] == T_DIR)
			ret += T_DIR_CODE << shift;
		else if (operation->argtypes[cnt] == T_IND)
			ret += T_IND_CODE << shift;
		shift -= 2;
		cnt += 1;
	}
	return (ret);
}

void	write_headers(t_asm *core)
{
	int fd;

	fd = core->core_fd;
	write_magic(fd);
	write_champ_name(core, fd);
	write_null(fd);
	write_exec_size(core, fd);
	write_champ_comment(core, fd);
	write_null(fd);
}