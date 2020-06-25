/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolopov <asolopov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 13:16:57 by asolopov          #+#    #+#             */
/*   Updated: 2020/06/25 12:52:50 by asolopov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	check_label(char *label, t_operation *oplist)
{
	while (oplist)
	{
		if (oplist->label)
		{
			if (ft_strequ(label, oplist->label))
				return (1);
		}
		oplist = oplist->next;
	}
	return (0);
}

int	check_t_reg(char *argum)
{
	int	reg_num;

	if (argum[0] != 'r')
		return (0);
	reg_num = ft_atoi(argum + 1);
	if (reg_num > REG_NUMBER || reg_num < 1)
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
	else if (ft_isdigit(argum[0]))
	{
		while (argum[cnt] != '\0')
		{
			if (!ft_isdigit(argum[cnt]))
				return (0);
			cnt += 1;
		}
		return (1);
	}
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
	else if (ft_isdigit(argum[1]))
	{
		while (argum[cnt] != '\0')
		{
			if (!ft_isdigit(argum[cnt]))
				return (0);
			cnt += 1;
		}
		return (1);
	}
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
	if (cnt == 16)
		ft_error_exit("No operation found!\n", 0, 0);
}

/*
void	create_op(void)
{
	t_operation *op_1;
	t_operation *op_2;
	t_operation *op_3;
	t_operation *cpy;
	t_operation *head;

	op_1 = (t_operation *)malloc(sizeof(t_operation));
	op_2 = (t_operation *)malloc(sizeof(t_operation));
	op_3 = (t_operation *)malloc(sizeof(t_operation));

	op_1->operation = "ld";
	op_1->label = "kaput";
	op_1->arg[0] = "3";
	op_1->arg[1] = "r5";
	op_1->arg[2] = 0;
	op_1->next = op_2;

	op_2->operation = "st";
	op_2->label = 0;
	op_2->arg[0] = "r1";
	op_2->arg[1] = "5";
	op_2->arg[2] = 0;
	op_2->next = op_3;
	
	op_3->operation = "zjmp";
	op_3->label = 0;
	op_3->arg[0] = "%10";
	op_3->arg[1] = 0;
	op_3->arg[2] = 0;
	op_3->next = 0;

	cpy = op_1;
	head = op_1;
	while (cpy)
	{
		check_operation(cpy, head);
		cpy = cpy->next;
	}
}*/