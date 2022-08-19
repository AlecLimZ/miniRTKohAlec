/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 10:56:24 by weng              #+#    #+#             */
/*   Updated: 2021/10/05 10:56:25 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Checks for an alphanumeric character. */
int	ft_isalnum(int c)
{
	return (ft_isalpha(c) == 1 || ft_isdigit(c) == 1);
}
