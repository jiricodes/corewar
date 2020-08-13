/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_checks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolopov <asolopov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 15:50:55 by jmakela           #+#    #+#             */
/*   Updated: 2020/07/29 14:26:43 by asolopov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		check_t_reg(char *argum)
{
	int	reg_num;

	if (argum[0] != 'r')
		return (0);
	reg_num = ft_atoi(argum + 1);
	if (reg_num > 99 || reg_num < 0)
		return (0);
	else
		return (1);
}

int		check_t_ind(char *argum)
{
	int cnt;

	cnt = 0;
	if (argum[0] == DIRECT_CHAR)
		return (0);
	if (is_special(argum, 0))
		return (1);
	else if (ft_isdigit(argum[0]) || (argum[0] == '-' && ft_isdigit(argum[1])))
	{
		if (argum[0] == '-')
			cnt = cnt + 1;
		while (argum[cnt] != '\0')
		{
			if (!ft_isdigit(argum[cnt]))
				return (0);
			cnt += 1;
		}
		return (1);
	}
	return (0);
}

int		check_t_dir(char *argum)
{
	int cnt;

	cnt = 1;
	if (argum[0] != DIRECT_CHAR)
		return (0);
	if (is_special(argum, 1))
		return (1);
	else if ((ft_isdigit(argum[1]) || (argum[1] == '-' &&
			ft_isdigit(argum[2]))) && (argum[2] != 'x' && argum[2] != 'X'))
	{
		if (argum[1] == '-')
			cnt = cnt + 1;
		while (argum[cnt] != '\0')
		{
			if (!ft_isdigit(argum[cnt]))
				return (0);
			cnt += 1;
		}
		return (1);
	}
	return (0);
}

int		check_argument(char *argum, t_asm *core)
{
	if (!argum)
	{
		ft_dprintf(2, "Missing instruction on line %d\n", core->line_cnt);
		ft_error("No argument provided!");
	}
	if (check_t_reg(argum) == 1)
		return (T_REG);
	else if (check_t_ind(argum) == 1)
		return (T_IND);
	else if (check_t_dir(argum) == 1)
		return (T_DIR);
	else
	{
		ft_dprintf(2, "Invalid instruction: \"%s\" on line %d\n", \
					argum, core->line_cnt);
		ft_error("Invalid argument provided!");
		return (0);
	}
}
