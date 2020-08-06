/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 10:41:12 by jnovotny          #+#    #+#             */
/*   Updated: 2020/08/06 11:39:08 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "libft.h"
# include "ft_error.h"
# include <stdint.h>
# include "op.h"
# include <ncurses.h>
# include <time.h>
# include <sys/ioctl.h>

/*
** Logging options:
** 0 - no log
** 1 - dev log (more details than -log flag)
*/

# define LOG 0
# define LOG_OPS 1
# define LOG_DETAILS 2
# define LOG_DEATHS 4
# define LOG_CTD 8
# define LOG_COPY_CAR 16
# define LOG_PC 32
# define LOG_FAIL_OPS 64
# define LOG_CAR_CNT 128

/*
** VFX settings
*/

# define VFX_WIDTH 64
# define VFX_SPEED_DELTA 500
# define VFX_INIT_SPEED 5000
# define VFX_ANIM_SPEED 50000
# define VFX_INFO_STD 30
# define VFX_LEGEND_STD 3

/*
** FLAGS Preset
*/

# define F_LOG_STR "1248"

/*
** VM Settings
*/

# define PLAYER_N_MAX 255

/*
** LOG Settings
*/

# define OP_STR	"[%zu]\tP %4zu | %s "
# define PC_STR	"[%zu]\tP %4zu | %zd -> %zd\n"

typedef struct	s_champ
{
	size_t		id;
	uint8_t		usr_id;
	int			fd;
	t_header	*header;
	uint8_t		*raw;
	size_t		car_cnt;
}				t_champ;

typedef struct	s_window
{
	WINDOW		*win;
	int			width;
	int			height;
	int			x;
	int			y;
}				t_win;

typedef struct	s_visual_settings
{
	t_win		*arena;
	t_win		*info;
	t_win		*legend;
	int			play;
	int			key;
	size_t		freq;
	uint8_t		*car_map;
}				t_vs;

typedef struct	s_args
{
	int			opcount;
	int			arg_cnt;
	int			arg_code;
	int			arg_types[3];
	int			arg[3];
	int			dir_size;
}				t_args;

typedef struct	s_carriage
{
	size_t				id;
	int32_t				reg[REG_NUMBER];
	int					carry;
	ssize_t				pc;
	ssize_t				step;
	int					op_index;
	size_t				cooldown;
	ssize_t				last_live;
	t_args				*args;
	struct s_carriage	*next;
}				t_car;

typedef struct	s_flags
{
	uint8_t		vfx;
	uint8_t		aff;
	uint8_t		log;
	uint8_t		large;
	uint8_t		silent;
	uint8_t		dump_size;
	size_t		dump_cycle;
}				t_flg;

typedef struct	s_vm
{
	int			n_players;
	t_champ		**champ;
	t_car		*car_list;
	size_t		car_id;
	size_t		car_cnt;
	uint8_t		*arena;
	uint8_t		*byte_owner;
	t_flg		*flags;
	t_vs		*vfx;
	t_champ		*last_to_live;
	ssize_t		cycles_to_die;
	ssize_t		check_cd;
	size_t		cycle;
	int			live_cnt;
	int			checks;
}				t_vm;

/*
** Champions and Arena Utilities
*/

t_champ			*init_champ(char	*filename, uint8_t id);
void			load_champ(t_champ *champ);
int32_t			decode(const uint8_t *source, size_t size);
void			init_arena(t_vm	*core);
void			print_arena(uint8_t *arena, int	size);
void			insert_champ_to_arena(t_vm *core, t_champ *champ,\
					ssize_t position);
void			delete_champs(t_champ **champs, int n);

/*
** Carriage Utils
*/

t_car			*create_carriage(size_t id, ssize_t	pc, uint8_t player_id);
t_car			*prepend_carriage(t_car *head, t_car *node);
t_car			*append_carriage(t_car *head, t_car *node);
t_car			*delete_carriage(t_car *head, size_t id);
void			delete_car_list(t_car *head);

/*
** Ncurses VFX
*/

t_vs			*init_visual_settings(void);
void			init_vfx_arena(t_vm *core);
void			draw_arena(t_vm *core, size_t limit);
void			draw_cycle(t_vm *core);
void			vfx_colors();
void			vfx_key(t_vm *core);
char			*create_progress_bar(size_t max_val, size_t cur_val,\
					size_t len, int *color);
void			reset_window(WINDOW *win, int playback);
int				check_carriage(t_car *head, ssize_t pos);
void			players_info(t_vm *core, int *x, int *y);
void			vfx_cycle(t_vm *core);
void			carriage_map(t_vm *core);

/*
** VM utilities
*/

void			engine(t_vm *core);
void			vfx_engine(t_vm *core);
void			process_vm_args(t_vm *core, char **argv, int argc);
size_t			check_player_id(t_vm *core, size_t number, int8_t mod);
void			clear_vm(t_vm *core);
void			vm_error(char *usr_msg);
void			print_usage(void);
void			introduce_champs(t_vm *core);
int32_t			decode_bytes(t_champ *champ, size_t size);
void			load_header(t_champ *champ);
void			load_code(t_champ *champ);
void			magic_check(t_champ *champ);
void			process_car(t_vm *core, t_car *car);
void			reset_car_cnt(t_vm *core);
t_car			*check_live_calls(t_vm *core, t_car *car, t_car **previous);
void			do_cycle(t_vm *core);
void			check_lives(t_vm *core);
size_t			find_player_nb(t_vm *core, size_t start);
int				handle_flags(t_vm *core, char **argv, int argc, int i);
void			process_dump(t_vm *core, char *cycle, char *size);
void			process_player(t_vm *core, char *number, char *filename);
int				ft_isnumber(const char *str);

/*
** Logging
*/

void			log_carriage(t_car *node);
void			log_champ(t_champ *champ, int index);
void			log_vm_status(t_vm *core);
void			log_car_in_arena(uint8_t *arena, int size, ssize_t car_pos);

/*
** OP read and utils
*/

void			get_step(t_car *car, t_args *args);
void			write_bytes(size_t index, int32_t val, t_car *car, t_vm *core);
void			copy_carriage(t_vm *core, t_car *car, int addr);
int				read_arg_type(uint8_t *arena, t_args *args, ssize_t index);
int				read_args(t_vm *core, t_args *args, ssize_t pos);
int				read_arena(uint8_t *arena, int start, int argval, int size);
int				mod(int a, int b);

#endif
