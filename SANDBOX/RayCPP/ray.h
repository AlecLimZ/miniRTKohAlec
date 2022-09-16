/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <-chu@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 17:21:46 by leng-chu          #+#    #+#             */
/*   Updated: 2022/09/16 14:27:02 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

class ray
{
	public:
		ray() {}
		ray(const point3 & origin, const vec3 & direction):
			orig(origin), dir(direction){}

		point3 getOrigin() const // point3 is vec3 but this role is 3D point
		{
			return orig;
		}
		vec3 getDirection() const
		{
			return dir;
		}

		point3 getAt(double t) const
		{
			return orig + (t * dir); // formula of position that point3 is at
		}

		point3	orig; // point3 is vec3
		vec3 	dir; // vec3 is vec3
};

#endif
