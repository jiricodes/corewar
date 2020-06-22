/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolopov <asolopov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 13:16:57 by asolopov          #+#    #+#             */
/*   Updated: 2020/06/18 17:29:43 by asolopov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	check_label(char *label, t_op *oplist)
{
	while (oplist)
	{
		if (oplist->label)
		{
			if (ft_strequ(label, oplist->label))
				return 1;
		}
		oplist = oplist->next;
	}
	return 0;
}

int	check_t_reg(char *argum)
{
	int	reg_num;

	if (argum[0] != 'r')
		return 0;
	reg_num = ft_atoi(argum + 1);
	if (reg_num > REG_NUMBER || reg_num < 1)
		return 0;
	else
		return 1;
}

int	check_t_ind(char *argum, t_op *oplist)
{
	int cnt;

	cnt = 0;
	if (argum[0] == LABEL_CHAR)
	{
		if (check_label(argum + 1, oplist) == 1)
			return 1;
		else
			return 0;
	}
	else if (isdigit(argum[0]))
	{
		while (argum[cnt] != '\0')
		{
			if (!isdigit(argum[cnt]))
				return 0;
			cnt += 1;
		}
		return 1;
	}
}

int		check_t_dir(char *argum, t_op *oplist)
{
	int cnt;

	cnt = 1;
	if (argum[0] != DIRECT_CHAR)
		return 0;
	if (argum[1] == LABEL_CHAR)
	{
		if (check_label(argum + 2, oplist) == 1)
			return 1;
		else
			return 0;
	}
	else if (isdigit(argum[1]))
	{
		while (argum[cnt] != '\0')
		{
			if (!isdigit(argum[cnt]))
			{
				printf("%c\n", argum[cnt]);
				return 0;
			}
			cnt += 1;
		}
		return 1;
	}
}

int	check_argument(char *argum, t_op *oplist)
{
	if (check_t_reg(argum) == 1)
		return T_REG;
	else if (check_t_ind(argum, oplist) == 1)
		return T_IND;
	else if (check_t_dir(argum, oplist) == 1)
		return T_DIR;
	else
	{
		printf("SUKA, ARGUMENT NO CORRECTO\n");
		return 0;
	}

}

void	check_further(t_op *operation, t_oplist reference, t_op *head)
{
	int	cnt;
	int	ret;

	cnt = 0;
	// check length of the op->args list!!!
	while (cnt < reference.arg_cnt)
	{
		printf("Checking arg: %s\n", operation->args[cnt]);
		ret = check_argument(operation->args[cnt], head);
		printf("\tret value: %d\n", ret);
		if ((ret | reference.arg_type[cnt]) == reference.arg_type[cnt] && ret != 0)
			printf("hehe boy\n");
		else
			printf("you're dead bitch\n");
		cnt += 1;
	}
}

void	check_operation(t_op *operation, t_op *head)
{
	int cnt;

	cnt = 0;
	while (cnt < 16)
	{
		if (ft_strequ(operation->opname, oplist[cnt].opname)) // also check number of args
		{
			printf("OPERATION: %s\n", operation->opname);
			check_further(operation, oplist[cnt], head);
			break ;
		}
		cnt += 1;
	}
	if (cnt == 16)
		ft_error_exit("No operation found!\n", 0, 0);
}

void	create_op(void)
{
	t_op *op_1;
	t_op *op_2;
	t_op *op_3;
	t_op *cpy;
	t_op *head;

	op_1 = (t_op *)malloc(sizeof(t_op));
	op_2 = (t_op *)malloc(sizeof(t_op));
	op_3 = (t_op *)malloc(sizeof(t_op));

	op_1->opname = "ld";
	op_1->label = "kaput";
	op_1->args[0] = "3";
	op_1->args[1] = "r5";
	op_1->args[2] = 0;
	op_1->next = op_2;

	op_2->opname = "st";
	op_2->label = 0;
	op_2->args[0] = "r1";
	op_2->args[1] = "5";
	op_2->args[2] = 0;
	op_2->next = op_3;
	
	op_3->opname = "zjmp";
	op_3->label = 0;
	op_3->args[0] = "%10";
	op_3->args[1] = 0;
	op_3->args[2] = 0;
	op_3->next = 0;

	cpy = op_1;
	head = op_1;
	while (cpy)
	{
		check_operation(cpy, head);
		cpy = cpy->next;
	}
}