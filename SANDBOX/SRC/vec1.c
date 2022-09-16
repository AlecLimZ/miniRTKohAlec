/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <-chu@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 18:24:00 by leng-chu          #+#    #+#             */
/*   Updated: 2022/09/15 18:42:48 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

double	ft_squared_len(const t_vec3 *v)
{
	return (v->rgb[0] * v->rgb[0]
		+ v->rgb[1] * v->rgb[1]
		+ v->rgb[2] * v->rgb[2]);
}

double	ft_length(const t_vec3 *v)
{
	return (sqrt(ft_squared_len(v)));
}
