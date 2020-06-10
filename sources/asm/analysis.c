#include "asm.h"

//Copies label/operation/instruction from start pos to end pos and returns it

char *split_instru(char *line, int start, int end)
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
	ft_printf("%s,", op); //just a testprint
	return(op);
}

//Finds positions where labels/operations/instructions should be split

int analysis(t_asm *core, char *line)
{
	int i;
	int start;
	int end;

	i = 0;
	start = 0;
	end = 0;
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
		if (start < end && end == i - 1)
			split_instru(line, start, end);
		/*
		** Maybe something along the lines of?:
		if (start < end && end == i - 1)
			ERROR_CHECK(split_instru(line, start, end));
		*/
	}
	return (1);
}