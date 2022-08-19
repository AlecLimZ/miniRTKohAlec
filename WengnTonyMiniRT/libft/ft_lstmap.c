/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 10:57:22 by weng              #+#    #+#             */
/*   Updated: 2022/06/11 22:20:46 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Iterates the list 'lst' and applies the function 'f' to the content of
each element. Creates a new list resulting of the successive
applications of the function 'f'. The 'del' function is used to delete
the content of an element if needed.
*/
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*first;
	t_list	*elem;

	if (lst == NULL || f == NULL)
		return (NULL);
	elem = ft_lstnew(f(lst->content));
	first = elem;
	if (elem != NULL)
	{
		lst = lst->next;
		while (lst != NULL)
		{
			elem = ft_lstnew(f(lst->content));
			if (elem != NULL)
				ft_lstadd_back(&first, elem);
			else
			{
				ft_lstclear(&first, del);
				return (NULL);
			}
			lst = lst->next;
		}
	}
	return (first);
}
