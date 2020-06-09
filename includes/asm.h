/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolopov <asolopov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 10:48:02 by jnovotny          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2020/06/08 23:35:03 by asolopov         ###   ########.fr       */
=======
/*   Updated: 2020/06/09 11:04:46 by jnovotny         ###   ########.fr       */
>>>>>>> 475a0fb39b2fe8582527a5c4ac63d78e60d0b4f5
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "op.h"
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
}				t_asm;


/*
** ASM struct utilities
*/

void	clear_t_asm(void *object);
char	*filename_pars(const char *source, const char *src_type,\
		const char *target_type);
t_asm	*intialize_asm(char *filename);
void	print_asmcore(t_asm *core);

/*
** ASM File reading
*/
void	read_file(t_asm *core, int source_fd);

#endif