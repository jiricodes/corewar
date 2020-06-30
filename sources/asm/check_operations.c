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

static int	check_label(char *label, t_operation *head)
{
	t_operation *cpy;

	cpy = head;
	while (cpy)
	{
		if (cpy->label)
		{
			if (ft_strequ(label, cpy->label))
				return (1);
		}
		cpy = cpy->next;
	}
	return (0);
}

int	check_t_reg(char *argum)
{
	int	reg_num;

	if (argum[0] != 'r')
		return (0);
	reg_num = ft_atoi(argum + 1);
	//corewar cookbook states that assembler should translate
	//everything between 0-99, even though over 16 are wrong
	//and it's arena's job to decide if it is correct or not?
	//if (reg_num > REG_NUMBER || reg_num < 1)
	//	return (0);
	if (reg_num > 99 || reg_num < 0)
		return (0);
	else
		return (1);
}

int	check_t_ind(char *argum, t_operation *oplist)
{
	int cnt;

	cnt = 0;
	if (argum[0] == LABEL_CHAR)
	{
		if (check_label(argum + 1, oplist) == 1)
			return (1);
		else
			return (0);
	}
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

int		check_t_dir(char *argum, t_operation *oplist)
{
	int cnt;

	cnt = 1;
	if (argum[0] != DIRECT_CHAR)
		return (0);
	if (argum[1] == LABEL_CHAR)
	{
		if (check_label(argum + 2, oplist) == 1)
			return (1);
		else
			return (0);
	}
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

int	check_argument(char *argum, t_operation *oplist)
{
	if (check_t_reg(argum) == 1)
		return (T_REG);
	else if (check_t_ind(argum, oplist) == 1)
		return (T_IND);
	else if (check_t_dir(argum, oplist) == 1)
		return (T_DIR);
	else
	{
		ft_printf("error was in argument: %s\n", argum);
		ft_error_exit("check_argument error", 0, 0);
		return (0);
	}

}

void	check_further(t_operation *operation, t_oplist ref, t_operation *head)
{
	int	cnt;
	int	ret;

	cnt = 0;
	// check length of the op->args list!!!
	while (cnt < ref.arg_cnt)
	{
		ret = check_argument(operation->arg[cnt], head);
		if ((ret | ref.arg_type[cnt]) == ref.arg_type[cnt] && ret != 0)
		{
			operation->argtypes[cnt] = ret;
		}
		else
			ft_error_exit("No operation found (check_further)", 0, 0);
		cnt += 1;
	}
	operation->arg_type_code = ref.arg_type_code;
	operation->op_code = ref.opcode;
}

//some issues if the last link has only label but nothing else
//for example Backward.s gives invalid argument since the last link is:
/*
label: l2
operation: (null)
arg1: (null)
arg2: (null)
arg3: (null)
op_size: 0
t_dir_size: 0
*/
void	check_operation(t_operation *operation, t_operation *head)
{
	int cnt;

	cnt = 0;
	while (cnt < 16)
	{
		if (ft_strequ(operation->op_name, oplist[cnt].opname)) // also check number of args
		{
			check_further(operation, oplist[cnt], head);
			break ;
		}
		cnt += 1;
	}
	//Added operation->label == NULL, so when there is no operation or args but label
	//it won't give error, maybe need to check there isn't anything else on the link?
	//need to figure out .extend (Backward.s)
	if (cnt == 16 && operation->label == NULL)
		ft_error_exit("No operation/label found!\n", 0, 0);
}
