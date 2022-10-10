/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <leng-chu@student.42kl.edu.m      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:14:56 by leng-chu          #+#    #+#             */
/*   Updated: 2022/09/26 11:33:20 by leng-chu         ###   ########.fr       */
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
	hits->records->t = root;
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
	hits->records->p = get_at(r, hits->records->t);
	hits->records->normal = new_minus2v(&hits->records->p,
			&hits->sphere.center);
	hits->records->normal = new_dividev(&hits->records->normal,
			hits->sphere.radius);
	return (1);
}

void	ft_setface(t_ray const *r, t_vec3 *outward_normal, t_hittable *hits)
{
	if (ft_dot(&r->dir, outward_normal) > 0.0)
	{
		hits->records->is_frontface = 0;
		ft_cvntminus(outward_normal);
		hits->records->normal = *outward_normal;
	}
	else
	{
		hits->records->is_frontface = 1;
		hits->records->normal = *outward_normal;
	}
}

// t_max for the closest so far
// this seems not work fully effective on all different objects in C...
// because it is for sphere only
int	ft_hitlists(t_ray *r, double t_min, double t_max)
{
	int			i;
	int			hit_anything;
	t_hittable	tmpr;

	hit_anything = 0;
	i = -1;
	while (hitlist[++i] != NULL)
	{
		if (ft_hitsphere(r, t_min, t_max, &tmpr))
		{
			hit_anything = 1;
			t_max = hitlist[i]->records->t;
			hitlist[i]->records = tmpr.records;
		}
	}
	return (hit_anything);
}
