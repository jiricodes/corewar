/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolopov <asolopov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 10:48:02 by jnovotny          #+#    #+#             */
/*   Updated: 2020/06/25 12:41:36 by asolopov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "op.h"
# include "oplist.h"
# include "libft.h"
# include "ft_error.h"

# define SRC_TYPE ".s"
# define TRGT_TYPE ".cor"

typedef struct	s_asm
{
	int		source_fd;
	int		core_fd;
	char	*champ_name;
	char	*champ_comment;
	int		flag;
}				t_asm;

//linked list struct
//we are not currently saving op_size and t_dir size
typedef struct s_operation
{
    char    *label;
    char    *op_name;
	
    char    *arg[3];
	int		argtypes[3];
	
    int     *op_size;
    int     t_dir_size;
	int		arg_type_code;
    struct s_operation *next;
}               t_operation;


/*
** ASM struct utilities
*/

void	clear_t_asm(void *object);
char	*filename_pars(const char *source, const char *src_type,\
		const char *target_type);
t_asm	*intialize_asm(char *filename);
void	print_asmcore(t_asm *core);
int		analysis(t_asm *core, char *line, t_operation **list);

/*
** ASM File reading
*/
void	read_file(t_asm *core, int source_fd, t_operation **list);

/*
** ASM List functions
*/
int     list_append(t_operation **head);
void    print_list(t_operation *list);


void	check_operation(t_operation *operation, t_operation *head);

#endif