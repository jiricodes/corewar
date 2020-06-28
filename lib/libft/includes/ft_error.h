/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 20:18:44 by jnovotny          #+#    #+#             */
/*   Updated: 2020/06/29 01:58:14 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ERROR_H
# define FT_ERROR_H

# include "libft.h"
# include <errno.h>
# include <stdio.h>

void	ft_error_exit(char *user_msg, void *memory, void (*del)(void *));

#endif
