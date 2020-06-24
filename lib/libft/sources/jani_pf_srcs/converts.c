/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converts.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakela <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 17:53:55 by jmakela           #+#    #+#             */
/*   Updated: 2020/06/24 13:08:49 by jmakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Finds out negativity and amount needed for allocation.
** Divides the number by base to find out how much space
** is required for allocation, checks for negativity and
** changes to number to positive for easier handling.
*/

static int		get_info(t_printf *pf)
{
	long long int	temp;
	int				i;

	i = 0;
	temp = pf->nbr;
	while (temp)
	{
		temp = temp / pf->base;
		i = i + 1;
	}
	if (pf->nbr < 0)
	{
		pf->nbr = pf->nbr * -1;
		pf->neg = 1;
	}
	else if (pf->nbr == 0)
		i = 1;
	return (i);
}

/*
** Converts integer to string.
** Using mask finds out the correct character(digit or alpha)
** by dividing the mask string by the base provided.
** Calls get_info to find out how much space is needed to
** allocate the string and if the number was negative or not.
** Keeps dividing the number by the base, until whole number
** is converted. returns allocated string.
*/

char			*convert(t_printf *pf)
{
	static char		chars1[] = "0123456789abcdef";
	char			*ptr;
	int				i;
	long long int	temp;

	i = get_info(pf);
	(!(ptr = (char*)malloc(sizeof(char) * (i + 1)))) ? exit(-1) : 0;
	ptr[i] = '\0';
	if (pf->nbr == 0)
		ptr[0] = '0';
	temp = pf->nbr;
	while (temp != 0)
	{
		i = i - 1;
		ptr[i] = chars1[temp % pf->base];
		temp = temp / pf->base;
	}
	return (ptr);
}

/*
** Gets length of the converted string.
** Divides the number by base to find out how much
** space should be allocated for the string.
*/

static int		get_len(t_printf *pf, unsigned long long int temp)
{
	int i;

	i = 0;
	while (temp)
	{
		temp = temp / pf->base;
		i = i + 1;
	}
	return (i);
}

/*
** Converts unsigned integer to a string.
** Using two masks(upper and lowercase), finds out
** the correct character(digit or alpha) by dividing
** the mask string by the base provided.
** Calls get_len, to calculate the amount of memory required.
** Checks if the number is zero and if not, keeps dividing
** it with base until whole number is converted.
** Returns allocated string.
*/

char			*u_convert(t_printf *pf)
{
	static char				chars1[] = "0123456789abcdef";
	static char				chars[] = "0123456789ABCDEF";
	char					*ptr;
	int						i;
	unsigned long long int	temp;

	temp = pf->unbr;
	i = get_len(pf, temp);
	(pf->unbr == 0) ? (i = 1) : 0;
	(!(ptr = (char*)malloc(sizeof(char) * (i + 1)))) ? exit(-1) : 0;
	ptr[i] = '\0';
	(pf->unbr == 0) ? (ptr[0] = '0') : 0;
	temp = pf->unbr;
	while (temp != 0)
	{
		i = i - 1;
		(pf->type == 'X') ? (ptr[i] = chars[temp % pf->base]) :
		(ptr[i] = chars1[temp % pf->base]);
		temp = temp / pf->base;
	}
	return (ptr);
}
