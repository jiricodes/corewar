/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolopov <asolopov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 10:48:02 by jnovotny          #+#    #+#             */
/*   Updated: 2020/06/30 13:57:18 by asolopov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "op.h"
# include "oplist.h"
# include "libft.h"
# include "ft_error.h"

#include <unistd.h>
#include <fcntl.h>

# define SRC_TYPE ".s"
# define TRGT_TYPE ".cor"

typedef struct	s_asm
{
	int		source_fd;
	int		core_fd;
	char	*champ_name;
	char	*champ_comment;
	int		byte_size;
}				t_asm;

//linked list struct
//next is finding label positions when they are used as arguments
typedef struct s_operation
{
    char    *label;
    char    *op_name;
	int		op_code;
	
    char    *arg[3];
	int		argtypes[3];
	
	//this links total size in bytes
    int     op_size;
    int     t_dir_size;
	int		arg_type_code;
	//start position of current link in bytecode
	int		position;
	//if argument has label, position where label points to is recorded here
	//example: arg[2] has :live, then label_pos[2] will have the bytecount to that label
	//if position is positive, it means label is after link, if negative, before link
	int		label_pos[3];
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
int		analysis(t_asm *core, char *line, t_operation **list, int total);

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
void	test_operation(t_asm *core, t_operation *op);
int		ft_chrpos(char *str, char c);
int		is_hex(char *argum);
char	*x_to_deci(char *argum);

#endif