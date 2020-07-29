/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolopov <asolopov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 13:16:57 by asolopov          #+#    #+#             */
/*   Updated: 2020/07/14 12:17:09 by asolopov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	check_further(t_operation *operation, t_oplist ref, t_asm *core)
{
	int	cnt;
	int	ret;

	cnt = 0;
	while (cnt < ref.arg_cnt)
	{
		ret = check_argument(operation->arg[cnt], core);
		if ((ret | ref.arg_type[cnt]) == ref.arg_type[cnt] && ret != 0)
			operation->argtypes[cnt] = ret;
		else
		{
			ft_dprintf(2, "argument error: %s\n", operation->arg[cnt]);
			ft_error_exit("No operation found (check_further)", 0, 0);
		}
		cnt += 1;
	}
	if (cnt < 3 && operation->arg[cnt])
	{
		ft_dprintf(2, "Too many arguments on row: %d\n", core->line_cnt);
		ft_error_exit("check_argument error", 0, 0);
	}
	operation->arg_type_code = ref.arg_type_code;
	operation->op_code = ref.opcode;
}

void	check_operation(t_operation *operation, t_asm *core)
{
	int cnt;

	cnt = 0;
	while (cnt < 16)
	{
		if (ft_strequ(operation->op_name, g_oplist[cnt].opname))
		{
			check_further(operation, g_oplist[cnt], core);
			break ;
		}
		cnt += 1;
	}
	if (cnt == 16)
	{
		ft_dprintf(2, "Invalid instruction: %s, on row %d\n", \
					operation->op_name, core->line_cnt);
		ft_error_exit("No operation/label found!\n", 0, 0);
	}
}
