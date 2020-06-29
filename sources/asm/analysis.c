#include "asm.h"

/*
** Test printer to see the contents of the linked list.
*/

void print_list(t_operation *list)
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
	ft_printf("\n");
}

//counts the size of one link
int count_bytes(t_operation *temp, int cnt)
{
	int bytes;
	int i;

	i = 0;
	bytes = 1;
	while (temp->arg[i] != NULL)
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

//Currently determines which is the t_dir_size, will call function to calculate
//argument type code and calculate size of link in bytes
int get_size_type(t_operation **list, int total)
{
	int cnt;

	cnt = 0;
	t_operation *temp;

	temp = *list;
	while (temp->next != NULL)
		temp = temp->next;
	if (temp->op_name)
	{
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
	temp->position = total;
	total = total + temp->op_size;
	return (total);
}

//Copies label/operation/instruction from start pos to end pos and returns it
//Doesn't work with multiple labels on the same row, need to fix (ex. live: live2: ...)
void	save_instru(t_operation **list, char *op)
{
	t_operation *temp;

	temp = *list;
	while (temp->next != NULL)
		temp = temp->next;
	if ((op[ft_strlen(op) - 1] == ':') && temp->label == NULL)
	{
		//dumb quickfix to get artems error check working for testing
		op[ft_strlen(op) - 1] = '\0';
		temp->label = ft_strdup(op);
	}
	else if (temp->op_name == NULL)
		temp->op_name = ft_strdup(op);
	else if (temp->arg[0] == NULL)
		temp->arg[0] = ft_strdup(op);
	else if (temp->arg[1] == NULL)
		temp->arg[1] = ft_strdup(op);
	else if (temp->arg[2] == NULL)
		temp->arg[2] = ft_strdup(op);
	free(op);
}

/*
** Splits the instructions and returns them.
*/

char		*split_instru(char *line, int start, int end)
{
	char *op;
	int i;

	i = 0;
	op = (char*)malloc(sizeof(char) * (end - start + 1));
	while (start <= end)
	{
		op[i] = line[start];
		i = i + 1;
		start = start + 1;
	}
	op[i] = '\0';
	return(op);
}

//Finds positions where labels/operations/instructions should be split
//Going to shorten and rework later, maybe with char mask and do something about the damn flag lol, it's a mess

int		analysis(t_asm *core, char *line, t_operation **list, int total)
{
	int i;
	int start;
	int end;
	int flag;

	i = 0;
	start = 0;
	end = 0;
	flag = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '#' || line[i] == ';')
			line[i] = '\0';
		if (((line[i] == ' ' || line[i] == '\t' || line[i] == ',') || i == 0) &&
			(line[i + 1] != ' ' && line[i + 1] != '\t' && line[i + 1] != ','))
		{
			(i == 0 && (line[i] != ' ' && line[i] != '\t' && line[i] != ',')) ? (start = 0) :
			(start = i + 1);
		}
		if (line[i] != '\0')
			i = i + 1;
		if ((line[i] == ' ' || line[i] == '\t' || line[i] == ',' || line[i] == '\0') &&
			(line[i - 1] != ' ' && line[i - 1] != '\t' && line[i - 1] != ','))
			end = i - 1;
		if (start <= end && end == i - 1 && end > 0)
		{
			flag = flag + 1;
			if (flag == 1)
				list_append(list);
			save_instru(list, split_instru(line, start, end));
		}
	}
	if (flag)
		total = get_size_type(list, total);
	return (total);
}