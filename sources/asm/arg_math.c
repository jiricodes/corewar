#include "asm.h"

//counts the size of one link
int count_bytes(t_operation *temp, int cnt)
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
			bytes = bytes + oplist[cnt].t_dir_size;
		else
			bytes = bytes + 2;
		i = i + 1;
	}
	if (oplist[cnt].arg_type_code)
		bytes = bytes + 1;
	return (bytes);
}

//Finds out t_dir_sizes from oplist and counts positions and total size
int get_size_type(t_operation **list, t_asm *core)
{
	int cnt;
	t_operation *temp;

	temp = *list;
	while (temp)
	{
		if (temp->op_name)
		{
			cnt = 0;
			while (cnt < 16)
			{
				if (ft_strequ(temp->op_name, oplist[cnt].opname))
				{
					temp->t_dir_size = oplist[cnt].t_dir_size;
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

//finds label ending position in argument and checks the byte position
int get_next_label(char *label, t_operation **head, t_operation *cur, int pos)
{
	int i;
	int total;
	char *temp;

	total = 0;
	i = pos;
	while (label[i] && label[i] != '+' && label[i] != '-')
		i = i + 1;
	temp = ft_strsub(label, pos, i - 1);
	total = find_position(head, cur, temp);
	free(temp);
	return (total);
}

//checks whether label has base or base 16 number
//transforms it from ascii to integer and returns it
int get_next_number(char *label)
{
	int i;
	int num;
	char c;
	char hexmask[] = "0123456789abcdefABCDEF";

	i = 0;
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

//bane of my existence and a massive piece of garbo
//arg_math determines what kind of arguments need to be added/substracted
//and does the math on them.
//basically we first check if we are dealing with direct or indirect
//then checks the first argument and loops until it finds no more arguments
//based on label chars we either find out label positions or digits/hexes
//hexes get converted to decimals and everything is counted together
//
//needs a lot of shortening, gonna do it later, fucking tired
int arg_math(char *label, t_operation **head, t_operation *cur, int cnt)
{
	int i;
	long long int total;
	int percent;
	int format;
	char *temp;

	i = 0;
	percent = 0;
	total = 0;
	if (label[0] == DIRECT_CHAR)
	{
		percent = 1;
		label = label + percent;
	}
	if (label[0] == LABEL_CHAR)
	{
		total = total + get_next_label(label, head, cur, 1);
		format = 1;
	}
	else
	{
		total = total + get_next_number(label);
		format = 2;
	}
	while (label[i])
	{
		if (label[i] == '+')
		{
			if (label[i + 1] == LABEL_CHAR)
				total = total + get_next_label(label, head, cur, i + 2);
			else
				total = total + get_next_number(label + i + 1);
		}
		else if (label[i] == '-')
		{
			if (label[i + 1] == LABEL_CHAR)
				total = total - get_next_label(label, head, cur, i + 2);
			else
				total = total - get_next_number(label + i + 1);
		}
		i = i + 1;
	}
	if (format)
		cur->label_pos[cnt] = total;
	else
	{
		free(cur->arg[cnt]);
		if (percent)
			cur->arg[cnt] = put_percent(ft_ultoa(total));
		else
			cur->arg[cnt] = ft_ultoa(total);
	}
}
