/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 10:57:28 by weng              #+#    #+#             */
/*   Updated: 2021/12/29 11:06:24 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Counts the number of elements in a list. */
int	ft_lstsize(t_list *lst)
{
	int	retval;

	retval = 0;
	while (lst != NULL)
	{
		retval++;
		lst = lst->next;
	}
	return (retval);
}
