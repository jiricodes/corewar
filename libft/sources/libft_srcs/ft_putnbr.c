/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 22:47:22 by jnovotny          #+#    #+#             */
/*   Updated: 2019/10/17 22:47:22 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putnbr_recursive(int nb)
{
	if (nb < 0)
	{
		ft_putnbr_recursive(nb / 10);
		ft_putchar(-1 * (nb % 10) + 48);
	}
	if (nb > 0)
	{
		ft_putnbr_recursive(nb / 10);
		ft_putchar(nb % 10 + 48);
	}
}

void		ft_putnbr(int n)
{
	if (n == +0 || n == -0)
	{
		ft_putchar('0');
	}
	if (n > 0)
	{
		ft_putnbr_recursive(n);
	}
	if (n < 0)
	{
		ft_putchar('-');
		ft_putnbr_recursive(n);
	}
}
