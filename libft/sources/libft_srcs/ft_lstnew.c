/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 10:22:51 by jnovotny          #+#    #+#             */
/*   Updated: 2019/10/21 10:30:19 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Allocates (with malloc(3)) and returns a “fresh” link. The variables
** content and content_size of the new link are initialized by copy
** of the parameters of the function. If the parameter content is nul,
** the variable content is initialized to NULL and the variable content_size
** is initialized to 0 even if the parameter content_size isn’t.
** The variable next is initialized to NULL.
** If the allocation fails, the function returns NULL.
*/

t_list			*ft_lstnew(void const *content, size_t content_size)
{
	t_list *head;

	head = (t_list*)malloc(sizeof(t_list));
	if (head == NULL)
		return (NULL);
	if (content == NULL)
	{
		head->content = NULL;
		head->content_size = 0;
	}
	else
	{
		head->content = malloc(content_size);
		if (head->content == NULL)
		{
			free(head);
			return (NULL);
		}
		ft_memcpy(head->content, content, content_size);
		head->content_size = content_size;
	}
	head->next = NULL;
	return (head);
}
