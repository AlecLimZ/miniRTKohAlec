/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 10:56:56 by weng              #+#    #+#             */
/*   Updated: 2021/10/05 10:56:56 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Adds the element 'new' at the end of the list. */
void	ft_lstadd_back(t_list **lst, t_list *new)
{
	if (new != NULL)
	{
		if (*lst != NULL)
			ft_lstlast(*lst)->next = new;
		else
			*lst = new;
	}
}
