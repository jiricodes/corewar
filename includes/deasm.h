/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deasm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolopov <asolopov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 12:43:35 by asolopov          #+#    #+#             */
/*   Updated: 2020/07/13 17:15:19 by asolopov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEASM_H
# define DEASM_H

# include "oplist.h"
# include "libft.h"
# include "ft_error.h"
# include "op.h"

# define SRC_TYPE ".cor"
# define TRGT_TYPE ".s"

typedef struct	s_operation
{
	char	*opname;
	
	int		arg_type_code;
	int		t_dir_size;
	
	char	*arg[3];
	int		argtypes[3];
}				t_operation;

typedef struct	s_deasm
{
	int	source_fd;
	int	target_fd;
	char	*champ_name;
	char	*champ_comment;
	int	exec_code_size;
	int8_t	*raw_code;
}				t_deasm;

void	read_file(t_deasm *core, int source_fd);

void	clear_t_deasm(void *object);

char	*filename_pars(const char *source, const char *src_type,\
		const char *target_type);
int32_t		decode(const uint8_t *source, size_t size);

#endif