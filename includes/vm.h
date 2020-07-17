/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolopov <asolopov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 10:41:12 by jnovotny          #+#    #+#             */
/*   Updated: 2020/07/17 12:51:02 by asolopov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "libft.h"
# include "ft_error.h"
# include <stdint.h>
# include "op.h"
# include "oplist.h"
# include <ncurses.h>

/*
** Logging options:
** 0 - no log
** 1 - in file log
** 2 - in file and on stdout
*/

# define LOG 2
# define LOG_FILE "cw_log.txt"

typedef struct s_champ
{
	uint8_t		id;
	int			fd;
	header_t	*header;
	uint8_t		*raw;
}				t_champ;

typedef struct	s_visual_settings
{
	int			width;
	int			height;
	WINDOW		*win;
}				t_vs;


typedef struct	s_vm
{
	int			n_players;
	t_champ		**champ;
	uint8_t		*arena;
	uint8_t		*byte_owner;
	t_vs		*vfx;
	int			last_player_to_report_live;
	size_t		cycles_to_die;
}				t_vm;

typedef struct	s_carriage
{
	size_t		id;
	int32_t		reg[REG_NUMBER];
	int			carry;
	ssize_t		pos;
	ssize_t		step;
	int			opcode;
	size_t		cooldown;
	size_t		last_live;
	struct s_carriage	*next;
}				t_car;

typedef struct	s_args
{
	int			opcount;
	int			arg_code;
	int			arg_types[3];
	int			arg[3];
	int			t_dir_size;
}				t_args;

/*
** Champion Utilities
*/

t_champ		*init_champ(char	*filename, int id);
void		load_champ(t_champ *champ);
int32_t		decode(const uint8_t *source, size_t size);
void		print_champ_header(t_champ *champ);
void		print_code(t_champ *champ);
void		init_arena(t_vm	*core);
void		insert_champ_to_arena(t_vm *core, t_champ *champ, ssize_t position);

/*
** Ncurses VFX, not sure if we want to use minilibx or other, this shit is for debuggin purposes atm
*/

t_vs		*init_visual_settings(char *title);
void		show_arena(t_vm *core);
void		vfx_colors();

/*
** VM utilities
*/

void		vm_log(char *message, ...);

#endif