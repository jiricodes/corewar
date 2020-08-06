#include "ft_error.h"

void	ft_error(char *user_msg)
{
	if (errno != 0)
		perror("SYSTEM ERROR MESSAGE: ");
	if (user_msg)
		ft_printf("%{RED}%{BOLD}USER ERROR MESSAGE%{EOC}: %s\n", user_msg);
	exit(-1);
}