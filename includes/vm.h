/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 10:41:12 by jnovotny          #+#    #+#             */
/*   Updated: 2020/07/27 17:28:39 by jnovotny         ###   ########.fr       */
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
# include <sys/ioctl.h>

/*
** Logging options:
** 0 - no log
** 1 - dev log (more details than -log flag)
*/

# define LOG 0
# define LOG_FILE "cw_log.txt"

/*
** VFX settings
*/

# define VFX core->flags->vfx
# define VFX_WIDTH 64
# define VFX_SLEEP_S 0
# define VFX_SLEEP_N 250000000
# define VFX_SPEED_DELTA 500
# define VFX_INIT_SPEED 5000
# define VFX_ANIM_SPEED 50000
# define VFX_INFO_STD 30
# define VFX_LEGEND_STD 3
# define VFX_PLAY core->vfx->play
# define VFX_ARENA core->vfx->arena->win
# define VFX_INFO core->vfx->info->win
# define VFX_LEG core->vfx->legend->win

/*
** FLAGS Preset
*/

# define F_LOG_STR "12"
# define F_LOG core->flags->log

/*
** VM Settings
*/

# define PLAYER_N_MAX 255

typedef struct s_champ
{
	size_t		id;
	uint8_t		usr_id;
	int			fd;
	header_t	*header;
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
	struct timespec time;
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
	int		cycles_to_die;
	int		check_cd;
	size_t		cycle;
	int			live_cnt;
	int			checks;
}				t_vm;

/*
** Champions and Arena Utilities
*/

t_champ		*init_champ(char	*filename, uint8_t id);
void		load_champ(t_champ *champ);
int32_t		decode(const uint8_t *source, size_t size);
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

/*
** Ncurses VFX, not sure if we want to use minilibx or other, this shit is for debuggin purposes atm
*/

t_vs		*init_visual_settings(void);
void		init_vfx_arena(t_vm *core);
void		draw_arena(t_vm *core, size_t limit);
void		draw_cycle(t_vm *core);
void		vfx_colors();
void		vfx_key(t_vm *core);

/*
** VM utilities
*/

void		engine(t_vm *core);
void		vfx_engine(t_vm *core);
void		process_vm_args(t_vm *core, char **argv, int argc);
size_t		check_player_id(t_vm *core, size_t number, int8_t mod);
void		clear_vm(t_vm *core);
void		vm_error(char *usr_msg, uint8_t log);
void		print_usage(void);
void		introduce_champs(t_vm *core);
int32_t		decode_bytes(t_champ *champ, size_t size);
void		load_header(t_champ *champ);
void		load_code(t_champ *champ);
void		magic_check(t_champ *champ);

/*
** Logging
*/

void		vm_log(uint8_t lvl, char *message, ...);
void		log_carriage(t_car *node, uint8_t log_lvl);
void		log_champ(t_champ *champ, int index, uint8_t log_lvl);
void		log_vm_status(t_vm *core, uint8_t log_lvl);
void		log_arena(uint8_t *arena, int size, uint8_t log_lvl);

/*
** OP read and utils
*/

void		fill_args(char *opname, t_args *args);
void		get_step(t_car *car, t_args *args);
void		write_bytes(size_t index, int val, t_car *car, t_vm *core);
void		copy_carriage(t_vm *core, t_car *car, int addr);

int			read_arg_type(uint8_t *arena, t_args *args, ssize_t index);
int			read_args(t_vm *core, t_args *args, ssize_t pos);
int			read_arena(uint8_t *arena, int start, int argval, int size);

#endif