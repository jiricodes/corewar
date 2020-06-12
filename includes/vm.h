/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 10:41:12 by jnovotny          #+#    #+#             */
/*   Updated: 2020/06/12 15:10:30 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "libft.h"
# include "ft_error.h"
# include <stdint.h>
# include "op.h"
# include <ncurses.h>

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
	t_champ		*champ;
	uint8_t		*arena;
	uint8_t		*byte_owner;
	t_vs		*vfx;
}				t_vm;

/*
** Champion Utilities
*/

t_champ		*init_champ(char	*filename);
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
#endif