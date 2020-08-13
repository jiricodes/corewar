/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 10:48:02 by jnovotny          #+#    #+#             */
/*   Updated: 2020/08/12 16:07:26 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "op.h"
# include "oplist_asm.h"
# include "libft.h"
# include "ft_error.h"

# define SRC_TYPE ".s"
# define TRGT_TYPE ".cor"

/*
** ASM core struct.
*/

typedef struct			s_asm
{
	int					source_fd;
	int					core_fd;
	char				*target_file;
	char				*champ_name;
	char				*champ_comment;
	int					byte_size;
	int					line_cnt;
}						t_asm;

/*
** ASM parser struct.
** Each t_operation holds one line of champ code.
** Line can have a labels, operation and arguments.
** In addition we record the types of arguments,
** size of the operation, size of t_dir, typecode,
** position in bytes, and label position, which is
** the position where argument label points to.
*/

typedef struct			s_operation
{
	char				*label;
	char				*op_name;
	int					op_code;
	char				*arg[3];
	int					argtypes[3];
	int					op_size;
	int					t_dir_size;
	int					arg_type_code;
	int					position;
	int					label_pos[3];
	int					line;
	struct s_operation	*next;
}						t_operation;

/*
** ASM struct utilities
*/

void					clear_t_asm(void *object);
char					*filename_pars(const char *source,\
						const char *src_type, const char *target_type);
t_asm					*intialize_asm(char *filename);
int						ft_chrpos(char *str, char c);
int						is_hex(char *argum);
char					*x_to_deci(char *argum);
int						is_special(char *argum, int func);

/*
** ASM File reading
*/

void					read_file(t_asm *core, int source_fd,\
						t_operation **list);

/*
** ASM Parsing
*/

void					lex_parser(t_asm *core, t_operation **list, char *line);
int						get_size_type(t_operation **list,\
										t_asm *core);
int						find_position(t_operation **list, t_operation *temp,\
										char *arg);
void					special_arg_finder(t_operation **head);
int						arg_math(t_operation **head, t_operation *cur,\
								char *label);
void					get_label_op(t_asm *core, t_operation **list,\
									char *line);
char					*strjoin_first(char *s1, char *s2);
char					*remove_trailing_spaces(char *src);
void					find_labels(t_operation **list);
void					get_hex(t_operation *new, char *line, int cnt);

/*
** ASM Error checking
*/

void					check_operation(t_operation *operation, t_asm *core);
void					match_labels(t_operation **head, int cnt,\
									int pos, int test);
int						check_label(char *label, t_operation **head, int line);
int						check_argument(char *argum, t_asm *core);
void					do_checks(t_asm *core, t_operation **list);
void					check_label_chars(char *label, int line);
void					check_lastline(int source_fd);
int						special_arg_check(char *label, t_operation **head, int line);
void					label_error(t_operation *finder, int cnt);

/*
** ASM List functions
*/

int						list_append(t_operation **head);

/*
** ASM Bytecode write functions
*/

void					write_champ_name(t_asm *core, int fd);
void					write_champ_comment(t_asm *core, int fd);
void					write_exec_size(t_asm *core, int fd);
void					write_null(int fd);
void					write_magic(int fd);
void					write_exec_code(t_asm *core, t_operation *op);
void					write_champion(t_asm *core, t_operation *op);

/*
** ASM Bytecode write helper functions
*/

int						get_arg_code(t_operation *operation);
void					write_headers(t_asm *core);
int						swap_int32(int val);
int						swap_int16(int val);

/*
** ASM Debug stuff
** REMOVE FOR FINAL VERSION
*/

void					print_asmcore(t_asm *core);
void					print_list(t_operation *list, t_asm *core);
void					print_op(t_operation *list);
#endif
