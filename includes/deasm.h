/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deasm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolopov <asolopov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 12:43:35 by asolopov          #+#    #+#             */
/*   Updated: 2020/07/29 15:21:38 by asolopov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEASM_H
# define DEASM_H

# include "oplist_asm.h"
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
	
	char	*arg[4];
	int		argtypes[4];
}				t_operation;

typedef struct	s_deasm
{
	int	source_fd;
	int	target_fd;
	char	*target_file;
	char	*champ_name;
	char	*champ_comment;
	int	exec_code_size;
	int8_t	*raw_code;
}				t_deasm;

/*
** DEASM Reading
*/

void			read_file(t_deasm *core, int source_fd);

/*
** DEASM Init & Clean
*/

t_operation		*init_op(t_operation *op);
t_deasm			*initialize_deasm(char *filename);
void			clear_t_deasm(void *object);

/*
** DEASM Decode Executable Code
*/

void			decode_exec(t_deasm *core, int8_t *rawcode);
int				decode_arg(t_operation *op, int cnt, int8_t *rawcode, int move);

/*
** DEASM Write
*/

void			write_header(int target_fd, t_deasm *core);
void			write_op(int target_fd, t_operation *op);

/*
** DEASM Utils
*/

char			*filename_pars(const char *source, const char *src_type,\
				const char *target_type);
int32_t			decode(const uint8_t *source, size_t size);

#endif