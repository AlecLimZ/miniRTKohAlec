/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 10:37:30 by weng              #+#    #+#             */
/*   Updated: 2022/05/20 10:47:02 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linalg.h"

/* Return a vector of size 2 */
t_vec	*ft_vec2_new(double x, double y)
{
	return (ft_vec_new(2, x, y));
}

/* Return a vector of size 3 */
t_vec	*ft_vec3_new(double x, double y, double z)
{
	return (ft_vec_new(3, x, y, z));
}

/* Return a vector of size 4 */
t_vec	*ft_vec4_new(double x, double y, double z, double w)
{
	return (ft_vec_new(4, x, y, z, w));
}
