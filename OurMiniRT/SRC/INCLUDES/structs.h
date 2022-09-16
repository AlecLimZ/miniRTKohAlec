/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Koh <Koh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:12:26 by Koh               #+#    #+#             */
/*   Updated: 2022/09/16 20:28:35 by Koh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# define MIN_COOR -999
# define MAX_COOR 999

enum e_object_type
{
	CYLINDER,
	SPHERE,
	PLANE,	
};

typedef union s_vec3
{
	double	elements[3];
	struct
	{
		double	x;
		double	y;
		double	z;
	};
	struct
	{
		double	r;
		double	g;
		double	b;
	};
}	t_vec3;

typedef t_vec3	t_rgb;
typedef t_vec3	t_xyz;

// only 1 ambient-light allowed (check "is_configured") 
typedef struct s_ambient
{
	double	ratio;
	t_rgb	color;
	int		is_configured;
}	t_ambient;

// only 1 camera allowed (check "is_configured") 
typedef struct s_camera
{
	double	fov;
	t_xyz	coor;
	t_xyz	orientation;
	int		is_configured;
}	t_camera;

// only 1 light allowed (check "is_configured") 
typedef struct s_light
{
	double	brightness;
	t_xyz	coor;
	t_rgb	color;
	int		is_configured;
}	t_light;

// can be sphere/plane/cylinder (as linked-list content)
typedef struct s_object
{
	double	diameter;
	double	height;
	t_xyz	coor;
	t_rgb	color;
	t_xyz	orientation;
	char	type;
}	t_object;

typedef struct s_image
{
	void	*ptr;
	int		*px;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_image;

// a scene only 1 ambient,camera,light
// may be multiple sphere/plane/cylinder objects 
typedef struct s_app
{
	unsigned int	last_updated;
	int				width;
	int				height;
	t_ambient		ambient;
	t_camera		camera;
	t_light			light;
	t_list			*objects;
	void			*mlx_ptr;
	void			*win_ptr;
	t_image			image;
}	t_app;

#endif
