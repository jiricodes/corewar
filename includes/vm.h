/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 10:41:12 by jnovotny          #+#    #+#             */
/*   Updated: 2020/06/10 13:40:19 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "libft.h"
# include "ft_error.h"
# include <stdint.h>
# include "op.h"

typedef struct s_champ
{
	uint		id;
	int			fd;
	header_t	*header;
	uint8_t		*raw;
}				t_champ;

typedef struct	s_vm
{
	t_champ		*champ;
}				t_vm;

/*
** Champion Utilities
*/

t_champ		*init_champ(char	*filename);
void		load_champ(t_champ *champ);
int32_t		decode(const uint8_t *source, size_t size);
void		print_champ_header(t_champ *champ);

#endif