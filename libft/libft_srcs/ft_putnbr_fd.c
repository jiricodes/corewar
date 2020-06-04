/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 22:47:14 by jnovotny          #+#    #+#             */
/*   Updated: 2019/10/17 22:47:14 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putnbr_recursive(int nb, int fd)
{
	if (nb < 0)
	{
		ft_putnbr_recursive(nb / 10, fd);
		ft_putchar_fd(-1 * (nb % 10) + 48, fd);
	}
	if (nb > 0)
	{
		ft_putnbr_recursive(nb / 10, fd);
		ft_putchar_fd(nb % 10 + 48, fd);
	}
}

void		ft_putnbr_fd(int n, int fd)
{
	if (n == +0 || n == -0)
	{
		ft_putchar_fd('0', fd);
	}
	if (n > 0)
	{
		ft_putnbr_recursive(n, fd);
	}
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		ft_putnbr_recursive(n, fd);
	}
}
