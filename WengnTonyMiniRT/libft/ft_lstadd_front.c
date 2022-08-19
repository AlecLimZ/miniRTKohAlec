/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 10:56:59 by weng              #+#    #+#             */
/*   Updated: 2021/10/05 10:57:02 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Adds the element 'new' at the beginning of the list. */
void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (new != NULL)
	{
		if (*lst != NULL)
			new->next = *lst;
		*lst = new;
	}
}
