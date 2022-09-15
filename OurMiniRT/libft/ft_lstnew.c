/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacklearn <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 15:48:48 by jacklearn         #+#    #+#             */
/*   Updated: 2021/05/19 15:54:42 by jacklearn        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*mlist;

	mlist = malloc(sizeof(t_list));
	if (mlist)
	{
		mlist->content = content;
		mlist->next = NULL;
	}
	return (mlist);
}
