/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_util2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <-chu@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 12:19:59 by leng-chu          #+#    #+#             */
/*   Updated: 2022/10/21 12:31:35 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	ft_checklight(const t_object *object)
{
	return (object->type == AMBIENT
		|| object->type == LIGHT
		|| object->type == LIGHT_BONUS);
}

void	adjust_val(float *value, float step, float lo, float hi)
{
	*value = clamp(*value + step, lo, hi);
}
