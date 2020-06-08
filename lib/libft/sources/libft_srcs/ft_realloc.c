/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 10:49:12 by jnovotny          #+#    #+#             */
/*   Updated: 2019/10/23 12:49:42 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** The realloc() function tries to change the size of the allocation pointed
** to by ptr to size, and returns ptr. If there is not enough room to enlarge
** the memory allocation pointed to by ptr, realloc() creates a new allocation,
** copies as much of the old data pointed to by ptr as will fit to the new
** allocation, frees the old allocation, and returns a pointer to the allocated
** memory. If ptr is NULL, realloc() is identical to a call to malloc()
** for size bytes.  If size is zero and ptr is not NULL, a new, minimum sized
** object is allocated and the original object is freed.
** When extending a region allocated with calloc(3), realloc(3) does not
** guarantee that the additional memory is also zero-filled.
*/

void	*ft_realloc(void *ptr, size_t original, size_t size)
{
	void	*new;

	if (!size && ptr)
	{
		if (!(new = ft_memalloc(1)))
			return (NULL);
		ft_memdel(&ptr);
		return (new);
	}
	if (!(new = ft_memalloc(size)))
		return (NULL);
	if (ptr)
	{
		ft_memmove(new, ptr, original);
		ft_memdel(&ptr);
	}
	return (new);
}
