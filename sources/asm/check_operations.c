/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 13:16:57 by asolopov          #+#    #+#             */
/*   Updated: 2020/06/29 01:53:48 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	check_t_reg(char *argum)
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

int	check_t_ind(char *argum)
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
	else if ((ft_isdigit(argum[1]) || (argum[1] == '-' && ft_isdigit(argum[2]))) && (argum[2] != 'x' && argum[2] != 'X'))
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

int	check_argument(char *argum, t_asm *core)
{
	if (!argum)
	{
		ft_printf("Missing instruction on row %d\n", core->line_cnt);
		ft_error_exit("check_argument error", 0, 0);
	}
	if (check_t_reg(argum) == 1)
		return (T_REG);
	else if (check_t_ind(argum) == 1)
		return (T_IND);
	else if (check_t_dir(argum) == 1)
		return (T_DIR);
	else
	{
		ft_printf("Invalid instruction: %s, on row %d\n", argum, core->line_cnt);
		ft_error_exit("check_argument error", 0, 0);
		return (0);
	}

}

void	check_further(t_operation *operation, t_oplist ref, t_asm *core)
{
	int	cnt;
	int	ret;

	cnt = 0;
	while (cnt < ref.arg_cnt)
	{
		ret = check_argument(operation->arg[cnt], core);
		if ((ret | ref.arg_type[cnt]) == ref.arg_type[cnt] && ret != 0)
		{
			operation->argtypes[cnt] = ret;
		}
		else
		{
			ft_printf("argument error: %s\n", operation->arg[cnt]);
			ft_error_exit("No operation found (check_further)", 0, 0);
		}
		cnt += 1;
	}
	if (cnt < 3 && operation->arg[cnt])
	{
		ft_printf("Too many arguments on row: %d\n", core->line_cnt);
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
		if (ft_strequ(operation->op_name, oplist[cnt].opname)) // also check number of args
		{
			check_further(operation, oplist[cnt], core);
			break ;
		}
		cnt += 1;
	}
	if (cnt == 16)
	{
		ft_printf("Invalid instruction: %s, on row %d\n", operation->op_name, core->line_cnt);
		ft_error_exit("No operation/label found!\n", 0, 0);
	}
}
