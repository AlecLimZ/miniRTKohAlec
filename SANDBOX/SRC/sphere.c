/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <leng-chu@student.42kl.edu.m      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:14:56 by leng-chu          #+#    #+#             */
/*   Updated: 2022/09/23 17:11:26 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hittable.h"

// Find the nearest root that lies in the accetable range
static int	find_root(t_hittable *hits, double const *t_min,
		double const *t_max, double const *d)
{
	double	root;
	double	sqrtd;

	sqrtd = sqrt(*d);
	root = (-hits->sphere.half_b - sqrtd) / hits->sphere.a;
	if (root < *t_min || *t_max < root)
	{
		root = (-hits->sphere.half_b + sqrtd) / hits->sphere.a;
		if (root < *t_min || *t_max < root)
			return (0);
	}
	hits->t = root;
	return (1);
}

int	ft_hitsphere(t_ray *r, double t_min, double t_max, t_hittable *hits)
{
	t_vec3	oc;
	double	discriminant;

	oc = new_minus2v(&r->orig, &hits->sphere.center);
	hits->sphere.a = ft_squared_len(&r->dir);
	hits->sphere.half_b = ft_dot(&oc, &r->dir);
	hits->sphere.c = ft_squared_len(&oc) - hits->sphere.radius
		* hits->sphere.radius;
	discriminant = hits->sphere.half_b * hits->sphere.half_b
		- hits->sphere.a * hits->sphere.c;
	if (discriminant < 0
		|| !find_root(hits, &t_min, &t_max, &discriminant))
		return (0);
	hits->p = get_at(r, hits->t);
	hits->normal = new_minus2v(&hits->p, &hits->sphere.center);
	hits->normal = new_dividev(&hits->normal, hits->sphere.radius);
	return (1);
}
