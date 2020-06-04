/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_strform.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 11:50:25 by jnovotny          #+#    #+#             */
/*   Updated: 2019/11/19 17:28:54 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_STRFORM_H
# define MY_STRFORM_H

# include "ft_printf.h"

/*
** COLORS
*/

# define C_RED			"\033[31m"
# define C_GREEN		"\033[32m"
# define C_YELLOW		"\033[33m"
# define C_BLUE			"\033[34m"
# define C_PURPLE		"\033[35m"
# define C_CYAN			"\033[36m"
# define C_EOC			"\033[0m"

/*
** FONT FORMAT
*/

# define F_BOLD			"\033[1m"
# define F_LIGHT		"\033[2m"
# define F_ITALIC		"\033[3m"
# define F_UNDERLINE	"\033[4m"
# define F_BLINK		"\033[5m"
# define F_INVERT		"\033[7m"
# define F_STRIKE		"\033[9m"
# define F_RESET		"\033[0m"

#endif
