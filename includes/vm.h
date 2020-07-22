/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolopov <asolopov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 10:41:12 by jnovotny          #+#    #+#             */
/*   Updated: 2020/07/22 12:35:40 by asolopov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "libft.h"
# include "ft_error.h"
# include <stdint.h>
# include "op.h"
// # include "oplist_cw.h"
# include <ncurses.h>
# include <time.h>
# include "vm_error.h"

/*
** Logging options:
** 0 - no log
** 1 - in file log
** 2 - in file and on stdout
*/

# define LOG 0
# define LOG_FILE "cw_log.txt"

/*
** VFX settings
*/

# define VFX 0
# define VFX_SLEEP_S 0
# define VFX_SLEEP_N 250000000
# define VFX_SPEED_DELTA 500
# define VFX_INIT_SPEED 5000

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
	int			play;
	int			key;
	size_t		freq;
	struct timespec time;
}				t_vs;

typedef struct	s_args
{
	int			opcount;
	int			arg_cnt;
	int			arg_code;
	int			arg_types[3];
	int			arg[3];
	int			t_dir_size;
}				t_args;

typedef struct	s_carriage
{
	size_t		id;
	int32_t		reg[REG_NUMBER];
	int			carry;
	ssize_t		pc;
	ssize_t		step;
	int			op_index;
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
	ssize_t		dump_cycle;
	int			dump_size;
	int			vfx_on;
	t_vs		*vfx;
	t_champ		*last_to_live;
	size_t		cycles_to_die;
	size_t		check_cd;
	size_t		cycle;
	int			live_cnt;
}				t_vm;

/*
** Champions and Arena Utilities
*/

t_champ		*init_champ(char	*filename, uint8_t id);
void		load_champ(t_champ *champ);
int32_t		decode(const uint8_t *source, size_t size);
void		print_champ_header(t_champ *champ);
void		print_code(t_champ *champ);
void		init_arena(t_vm	*core);
void		print_arena(uint8_t *arena, int	size);
void		insert_champ_to_arena(t_vm *core, t_champ *champ, ssize_t position);
void		delete_champs(t_champ **champs, int n);


/*
** Carriage Utils
*/

t_car		*create_carriage(size_t id, ssize_t	pc, uint8_t player_id);
t_car		*prepend_carriage(t_car *head, t_car *node);
t_car		*append_carriage(t_car *head, t_car *node);
t_car		*delete_carriage(t_car *head, size_t id);
void		delete_car_list(t_car *head);
void		log_carriage(t_car *node);

/*
** Ncurses VFX, not sure if we want to use minilibx or other, this shit is for debuggin purposes atm
*/

t_vs		*init_visual_settings(char *title);
void		init_vfx_arena(t_vm *core);
void		draw_arena(t_vm *core);
void		vfx_colors();
void		vfx_key(t_vs *vfx);

/*
** VM utilities
*/

void		vm_log(char *message, ...);
void		engine(t_vm *core);
void		write_byte_arena(t_vm *core, ssize_t origin_pc, ssize_t position, uint8_t byte);
void		process_vm_args(t_vm *core, char **argv, int argc);

/*
** OP funcs
*/

void		fill_args(char *opname, t_args *args);
int			check_types(int *types, const int *reference);
int			read_arg_type(t_args *args, int8_t byte);
void		get_jump(t_car *car, t_args *args);
void		write_bytes(uint8_t *start, int size, int val);
void		read_args(uint8_t *code, t_args *args);
int			get_tind(int argval, uint8_t *code);

#endif