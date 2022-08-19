/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 09:06:59 by hloke             #+#    #+#             */
/*   Updated: 2022/06/11 11:11:11 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

/* Return the size of a NULL terminated array of pointers. */
size_t	ft_array_size(const void *array)
{
	const void	**arr;
	size_t		num;

	arr = (const void **)array;
	num = 0;
	if (arr != NULL)
	{
		while (arr[num] != NULL)
			++num;
	}
	return (num);
}

/* Deletes the elements pointed to by the pointers in a NULL terminated
 * array of pointers 'ptr' using the function 'del', free the array
 * itself. */
void	ft_array_del(void *ptr, void (*del)(void *))
{
	void	**elem;

	if (ptr == NULL)
		return ;
	if (del != NULL)
	{
		elem = ptr;
		while (*elem != NULL)
			del(*elem++);
	}
	free(ptr);
}
