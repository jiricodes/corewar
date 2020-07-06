/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolopov <asolopov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 10:57:41 by jnovotny          #+#    #+#             */
/*   Updated: 2020/06/25 15:17:08 by asolopov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_asm	*intialize_asm(char *filename)
{
	t_asm	*core;
	char	*target_file;

	core = (t_asm *)ft_memalloc(sizeof(t_asm));
	if (!core)
		ft_error_exit("Malloc at initialize_asm", NULL, NULL);
	target_file = filename_pars(filename, SRC_TYPE, TRGT_TYPE);
	if (!target_file)
		ft_error_exit("Given file is of incorrect type", (void *)core, clear_t_asm);
	core->source_fd = open(filename, O_RDONLY);
	if (core->source_fd < 0)
		ft_error_exit("Failed to open given source file", (void *)core, clear_t_asm);
	core->core_fd = open(target_file, O_RDWR | O_CREAT, 0600);
	if (core->core_fd < 0)
		ft_error_exit("Failed to open given target file", (void *)core, clear_t_asm);
	core->byte_size = 0;
	core->line_cnt = 0;
	return (core);
}

/*
** Function to add a node to the linked list struct.
** Allocates memory and initializes all values to null.
*/

t_operation	*newnode(void)
{
	t_operation *new;

	new = (t_operation*)ft_memalloc(sizeof(t_operation));
	if (!new)
		ft_error_exit("Malloc at newnode", NULL, NULL);
	new->label = NULL;
	new->op_name = NULL;
	new->arg[0] = NULL;
	new->arg[1] = NULL;
	new->arg[2] = NULL;
	new->argtypes[0] = 0;
	new->argtypes[1] = 0;
	new->argtypes[2] = 0;
	new->next = NULL;
	new->op_size = 0;
	new->t_dir_size = 0;
	new->op_code = 0;
	new->position = 0;
	new->label_pos[0] = 0;
	new->label_pos[1] = 0;
	new->label_pos[2] = 0;
	return (new);
}

/*
** Function to append a new link to the end of the list
** Goes through the list and calls for newnode to allocate and initialize the new node.
*/

int	list_append(t_operation **head)
{
	t_operation *last;

	last = *head;
	if (*head == NULL)
	{
		*head = newnode();
		return (1);
	}
	while (last->next != NULL)
		last = last->next;
	last->next = newnode();
	return (1);
}

//finds first occurrence of c in str
//so basically strchr, but returns -1 instead of null
//made it easier for me to check positions
int ft_chrpos(char *str, char c)
{
	int i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i = i + 1;
	}
	return (-1);
}

//determines if argum string is hex
//each char has to be part of hexmask string
//else not hex
int				is_hex(char *argum)
{
	int i;
	char hexmask[] = "0123456789abcdefABCDEF";

	if (argum[0] == DIRECT_CHAR)
		i = 3;
	else
		i = 2;
	if (argum[i - 2] == '0' && (argum[i-1] == 'x' || argum[i-1] == 'X'))
	{
		while (argum[i] != '\0')
		{
			if (ft_chrpos(hexmask, argum[i]) < 0)
				return (0);
			i = i + 1;
		}
		return (1);
	}
	return (0);
}

//rises number to the power
//it is being used to convert hex to decimal
unsigned long			ft_pow(int number, int power)
{
	unsigned long total;

	total = number;
	if (!power)
		return (1);
	else if (power == 1)
		return (number);
	else
	{
		while (power > 1)
		{
			total = total * number;
			power = power - 1;
		}
	}
	return (total);
}

//appends % sign in front of the string
//needed it for hex conversions of direct arguments
char 		*put_percent(char *str)
{
	int i;
	int len;
	char *final;

	i = 0;
	len = ft_strlen(str);
	final = (char*)malloc(sizeof(char*) * len + 2);
	final[0] = DIRECT_CHAR;
	while(str[i])
	{
		final[i+1] = str[i];
		i = i + 1;
	}
	final[i + 1] = '\0';
	return (final);
}

//converts hex to decimal.
char			*x_to_deci(char *argum)
{
	unsigned long hex;
	int len;
	int val;
	int i;

	hex = 0;
	len = ft_strlen(argum);
	val = 0;
	if (argum[0] == DIRECT_CHAR)
	{
		len = len - 4;
		i = 3;
	}
	else
	{
		len = len - 3;
		i = 2;
	}
	while (argum[i] != '\0')
	{
		if (argum[i] >= '0' && argum[i] <= '9')
			val = argum[i] - 48;
		else if (argum[i] >= 'a' && argum[i] <= 'f')
			val = argum[i] - 97 + 10;
		else if (argum[i] >= 'A' && argum[i] <= 'F')
			val = argum[i] - 65 + 10;
		hex = hex + (val * ft_pow(16, len));
		len = len - 1;
		i = i + 1;
	}
	return(ft_ultoa(hex));
}

/*
** Test printer to see the contents of the linked list.
*/

void print_list(t_operation *list, t_asm *core)
{
	while (list != NULL)
	{
		ft_printf("\nlabel: %s, position: %d\n", list->label, list->position);
		ft_printf("operation: %s\n", list->op_name);
		ft_printf("arg1: %s\n", list->arg[0]);
		ft_printf("arg2: %s\n", list->arg[1]);
		ft_printf("arg3: %s\n", list->arg[2]);
		ft_printf("labelpos1: %d\n", list->label_pos[0]);
		ft_printf("labelpos2: %d\n", list->label_pos[1]);
		ft_printf("labelpos3: %d\n", list->label_pos[2]);
		ft_printf("op_size: %d\n", list->op_size);
		ft_printf("t_dir_size: %d\n", list->t_dir_size);
		ft_printf("arg1 TYPE: %d\n", list->argtypes[0]);
		ft_printf("arg2 TYPE: %d\n", list->argtypes[1]);
		ft_printf("arg3 TYPE: %d\n", list->argtypes[2]);
		ft_printf("has arg type code?: %d\n", list->arg_type_code);
		list = list->next;
	}
	ft_printf("Total size in bytes: %d\n", core->byte_size);
	ft_printf("\n");
}