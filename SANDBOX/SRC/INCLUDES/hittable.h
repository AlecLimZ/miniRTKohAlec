/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hittable.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <leng-chu@student.42kl.edu.m      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:01:03 by leng-chu          #+#    #+#             */
/*   Updated: 2022/09/26 11:35:48 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HITTABLE_H
# define HITTABLE_H

# include "vecray.h"
# include "libft.h"

typedef struct s_list	t_list;

typedef struct s_sphere
{
	t_point3	center;
	double		radius;
	double		a;
	double		half_b;
	double		c;
}	t_sphere;

typedef struct s_hitrecord
{
	t_point3	p;
	t_vec3		normal;
	double		t;
	int			is_frontface;
}	t_hitrecord;

typedef struct s_hittable
{
	t_hitrecord	*records;
	t_sphere	sphere;
}	t_hittable;

t_hittable	**hitlist;

int	ft_hitsphere(t_ray *r, double t_min, double t_max, t_hittable *hits);
int	ft_hitlists(t_ray *r, double t_min, double t_max);

#endif
