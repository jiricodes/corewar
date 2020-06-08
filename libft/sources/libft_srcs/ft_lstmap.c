/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 11:15:01 by jnovotny          #+#    #+#             */
/*   Updated: 2019/10/21 11:37:51 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Iterates a list lst and applies the function f to each link to
** create a “fresh” list (using malloc(3)) resulting from the successive
** applications of f. If the allocation fails, the function returns NULL.
*/

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *fresh;
	t_list *node;
	t_list *head;

	if (!f || !lst)
		return (NULL);
	if (!(node = f(lst)))
		return (NULL);
	if (!(fresh = ft_lstnew(node->content, node->content_size)))
		return (NULL);
	head = fresh;
	while (lst->next)
	{
		lst = lst->next;
		if (!(node = f(lst)))
			return (NULL);
		if (!(fresh->next = ft_lstnew(node->content, node->content_size)))
			return (NULL);
		fresh = fresh->next;
	}
	return (head);
}
