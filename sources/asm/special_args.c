#include "asm.h"

//check label originally from check_operations, no changes
//moved here because labels are not checked with other args
int	check_label(char *label, t_operation **head)
{
	t_operation *cpy;

	cpy = *head;
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

//checks arguments that have format: %:l1 -4 + :l2 OR :live -:l1 + 5 - 0xff
//basically splits the arg into chunks and calls individual checks on each
//first labels, then hexes and finally digits
int special_arg_check(char *label, t_operation **head)
{
	int i;
	int start;
	char *temp;
	char hexmask[] = "0123456789abcdefABCDEF";

	i = 0;
	start = 0;
	if (label[0] == DIRECT_CHAR)
		i = 1;
	while (label[i])
	{
		if (label[i] == LABEL_CHAR)
		{
			start = i + 1;
			while(label[i] != '+' && label[i] != '-' && label[i])
				i = i + 1;
			temp = ft_strsub(label, start, i - start);
			if (!check_label(temp, head))
				return (0);
			free(temp);
		}
		else if (label[i] == '0' && (label[i + 1] == 'x' || label[i + 1] == 'X'))
		{
			i = i + 2;
			if (label[i])
			{
				while (ft_chrpos(hexmask, label[i]) >= 0)
					i = i + 1;
				if (label[i] != '\0' && label[i] != '+' && label[i] != '-')
					return (0);
			}
			else
				return (0);
		}
		else if (ft_isdigit(label[i]))
		{
			while(ft_isdigit(label[i]))
				i = i + 1;
			if (label[i] != '\0' && label[i] != '+' && label[i] != '-')
				return (0);
		}
		if (label[i] == '-' || label[i] == '+')
			i = i + 1;
		else if (label[i] != '\0')
			return (0);
	}
	return(1);
}

//determines if argument is special
//special arguments have multiple parts that need calculation
//func is used to determine if special was called as direct or indirect argument
int is_special(char *argum, int func)
{
	int pos;

	pos = 0;
	if (argum[1] == LABEL_CHAR && func)
		return (1);
	else if (argum[0] == LABEL_CHAR && !func)
		return (1);
	else if (func)
		pos = 1;
	if (ft_chrpos(argum, '+') > pos || ft_chrpos(argum, '-') > pos)
		return (1);
	else if (is_hex(argum))
		return (1);
	return (0);
}

//checks special arguments for argument math
//determined by having +/- somewhere in the middle
//pos makes sure that number like -50 or %-50 don't trigger arg_math
void	special_arg_finder(t_operation **head)
{
	t_operation *finder;
	int cnt;
	int pos;

	finder = *head;
	while (finder)
	{
		cnt = 0;
		while (finder->arg[cnt] && cnt < 3)
		{
			(finder->arg[cnt][0] == DIRECT_CHAR) ? (pos = 1) :
			(pos = 0);
			if ((ft_chrpos(finder->arg[cnt], '+') > pos) || (ft_chrpos(finder->arg[cnt], '-') > pos))
				arg_math(finder->arg[cnt], head, finder, cnt);
			cnt += 1;
		}
		finder = finder->next;
	}
}

// added special argument checking for match labels
// if +/- is found somewhere in the middle of argument
// special arg check is called to verify the argument
void	match_labels(t_operation **head)
{
	t_operation *finder;
	int cnt;
	int pos;
	int test;

	finder = *head;
	test = 1;
	while (finder)
	{
		cnt = 0;
		while (finder->arg[cnt] && cnt < 3)
		{
			(finder->arg[cnt][0] == DIRECT_CHAR) ? (pos = 1) :
			(pos = 0);
			if (ft_chrpos(finder->arg[cnt], '+') > pos || ft_chrpos(finder->arg[cnt], '-') > pos)
				test = special_arg_check(finder->arg[cnt], head);
			else
			{
				if (finder->arg[cnt][pos] == LABEL_CHAR)
					test = check_label(finder->arg[cnt] + pos + 1, head);
			}
			if (!test)
			{
				ft_printf("erroneous argument = %s\n", finder->arg[cnt]);
				ft_error_exit("Argument error.\n", 0, 0);	
			}
			cnt += 1;
		}
		finder = finder->next;
	}
}