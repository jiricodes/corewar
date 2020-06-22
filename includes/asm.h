/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolopov <asolopov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 10:48:02 by jnovotny          #+#    #+#             */
/*   Updated: 2020/06/18 16:57:55 by asolopov         ###   ########.fr       */
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

typedef struct s_ops
{
	char			*label;
	char			*opname;
	char			*args[3];
	int				t_dir_size;
	int				opsize;
	struct s_ops	*next;
}				t_op;


/*
** ASM struct utilities
*/

void	clear_t_asm(void *object);
char	*filename_pars(const char *source, const char *src_type,\
		const char *target_type);
t_asm	*intialize_asm(char *filename);
void	print_asmcore(t_asm *core);
int		analysis(t_asm *core, char *line);

/*
** ASM File reading
*/
void	read_file(t_asm *core, int source_fd);

#endif