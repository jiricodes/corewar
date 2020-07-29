/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_math.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakela <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 15:20:12 by jmakela           #+#    #+#             */
/*   Updated: 2020/07/23 15:20:17 by jmakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** Counts the size of one link.
*/

int	count_bytes(t_operation *temp, int cnt)
{
	int bytes;
	int i;

	i = 0;
	bytes = 1;
	while (temp->arg[i] != NULL && i < 3)
	{
		if (temp->arg[i][0] == 'r')
			bytes = bytes + 1;
		else if (temp->arg[i][0] == DIRECT_CHAR)
			bytes = bytes + g_oplist[cnt].t_dir_size;
		else
			bytes = bytes + 2;
		i = i + 1;
	}
	if (g_oplist[cnt].arg_type_code)
		bytes = bytes + 1;
	return (bytes);
}

/*
** Finds out t_dir_sizes from g_oplist and counts positions and total size.
*/

int	get_size_type(t_operation **list, t_asm *core)
{
	int			cnt;
	t_operation	*temp;

	temp = *list;
	while (temp)
	{
		if (temp->op_name)
		{
			cnt = 0;
			while (cnt < 16)
			{
				if (ft_strequ(temp->op_name, g_oplist[cnt].opname))
				{
					temp->t_dir_size = g_oplist[cnt].t_dir_size;
					break ;
				}
				cnt += 1;
			}
			temp->op_size = count_bytes(temp, cnt);
		}
		temp->position = core->byte_size;
		core->byte_size = core->byte_size + temp->op_size;
		temp = temp->next;
	}
	return (0);
}

/*
** Finds label ending position in argument and checks the byte position.
*/

int	get_next_label(char *label, t_operation **head, t_operation *cur, int pos)
{
	int		i;
	int		total;
	char	*temp;

	total = 0;
	i = pos;
	while (label[i] && label[i] != '+' && label[i] != '-')
		i = i + 1;
	temp = ft_strsub(label, pos, i - 1);
	total = find_position(head, cur, temp);
	free(temp);
	return (total);
}

int	get_next_number(char *label, int i)
{
	int			num;
	char		c;
	static char	hexmask[] = "0123456789abcdefABCDEF";

	if (label[0] == '0' && (label[1] == 'x' || label[1] == 'X'))
	{
		i = 2;
		while (ft_chrpos(hexmask, label[i]) >= 0)
			i = i + 1;
		c = label[i];
		label[i] = '\0';
		num = ft_atoi(x_to_deci(label));
		label[i] = c;
	}
	else
	{
		while (ft_isdigit(label[i]))
			i = i + 1;
		c = label[i];
		label[i] = '\0';
		num = ft_atoi(label);
		label[i] = c;
	}
	return (num);
}

/*
** Determines the types of arguments that need math.
** Check if direct or indirect, keep looping args.
*/

int	arg_math(t_operation **head, t_operation *cur, char *label)
{
	int				i;
	int				sign;
	long long int	total;

	i = 0;
	sign = 1;
	total = 0;
	(label[0] == DIRECT_CHAR) ? (label += 1) : 0;
	(label[0] == LABEL_CHAR) ? (total += get_next_label(label, head, cur, 1)) :
	(total += get_next_number(label, 0));
	while (label[i])
	{
		(label[i] == '-') ? (sign = -1) : 0;
		(label[i + 1] == LABEL_CHAR) ? (total +=
		(sign * get_next_label(label, head, cur, i + 2))) :
		(total += (sign * get_next_number(label + i + 1, 0)));
		sign = 1;
		i += 1;
	}
	return (total);
}
