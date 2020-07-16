/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 10:41:12 by jnovotny          #+#    #+#             */
/*   Updated: 2020/07/16 17:33:33 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "libft.h"
# include "ft_error.h"
# include <stdint.h>
# include "op.h"
# include <ncurses.h>

/*
** Logging options:
** 0 - no log
** 1 - in file log
** 2 - in file and on stdout
*/

# define LOG 2
# define LOG_FILE "cw_log.txt"

typedef struct	s_args
{
	int			arg_step;
	int			arg_code;
	int			arg_types[3];
	int			args[3];
}				t_args;

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

typedef struct	s_carriage
{
	size_t		id;
	int32_t		reg[REG_NUMBER];
	int			carry;
	ssize_t		pc;
	ssize_t		step;
	int			opcode;
	size_t		cooldown;
	size_t		last_live;
	t_args		*args;
	struct s_carriage	*next;
}				t_car;

typedef struct	s_vm
{
	int			n_players;
	t_champ		**champ;
	t_car		*car_list;
	size_t		car_id;
	uint8_t		*arena;
	uint8_t		*byte_owner;
	t_vs		*vfx;
	uint8_t		last_player_to_report_live;
	size_t		cycles_to_die;
	size_t		check_cd;
	size_t		cycle;
	int			live_cnt;
}				t_vm;


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
** Carriage Utils
*/

t_car		*create_carriage(size_t id, ssize_t	pc, uint8_t player_id);
t_car		*prepend_carriage(t_car *head, t_car *node);
t_car		*append_carriage(t_car *head, t_car *node);
t_car		*delete_carriage(t_car *head, size_t id);
void		delete_car_list(t_car *head);

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
void		engine(t_vm *core);

#endif