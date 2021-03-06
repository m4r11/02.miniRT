/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldeta <mvaldeta@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 16:28:37 by mavaldeta         #+#    #+#             */
/*   Updated: 2021/10/18 14:36:02 by mvaldeta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** LIB: none
** PARAM: #1. The adress of a pointer to an element.
** #2. The adress of the function used to iterate on the list.
** #3. The adress of the function used to delete
** the content of an element if needed.
** DESC: Iterates the list ’lst’ and applies the function ’f’
** to the content of each element.
** Creates a new list resulting of the successive
** applications of the function ’f’.
** The ’del’ function is used to delete the content of an element if needed.
** Returns the new list.
** (｡◕‿◕｡)
*/

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlist;
	t_list	*node;

	node = NULL;
	if (!f || !del)
		return (NULL);
	while (lst != NULL)
	{
		if (node == NULL)
		{
			newlist = ft_lstnew(f(lst->content));
			if (!(newlist))
				return (NULL);
			node = newlist;
		}
		else
		{
			node->next = ft_lstnew(f(lst->content));
			if (!node->next)
				ft_lstclear(&newlist, del);
			node = node->next;
		}
		lst = lst->next;
	}
	return (newlist);
}
