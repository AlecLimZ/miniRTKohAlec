/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Koh <Koh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:12:26 by Koh               #+#    #+#             */
/*   Updated: 2022/10/21 12:14:47 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
# include <stdbool.h>
# include "libft.h"

# define FEATURE_GAMMA_CORRECTION	1
# define FEATURE_REFLECTION	2
# define FEATURE_SPECULAR	4
# define FEATURE_LIGHT	8
# define FEATURE_NORMAL 16
# define FEATURE_SMALLER_WINDOW 32
# define FEATURE_HELP 64
# define FEATURE_CAPTION 128
# define KEY_SHIFT_FLAG 1
# define KEY_CTRL_FLAG 2

enum e_object_type
{
	AMBIENT,
	CAMERA,
	LIGHT,
	LIGHT_BONUS,
	SPHERE,
	PLANE,	
	CYLINDER,
	CONE,
	END_OF_OBJECT_TYPE,
	OBJECT_TYPE_COUNT = END_OF_OBJECT_TYPE,
	OBJECT_TYPE_ERROR,
};

typedef union s_vec3
{
	float		e[3];
	struct
	{
		float	x;
		float	y;
		float	z;
	};
}	t_vec3;

typedef struct s_ray
{
	t_vec3	orig;
	t_vec3	dir;
	t_vec3	norm;
	float	y;
}	t_ray;

// tinyraytracer: albedo[diffuse, specular, reflect]
typedef struct s_material {
	float	albedo[3];
	float	specular_exponent;
	t_vec3	diffuse_color;
}	t_material;

// all raytracing objects as linked-list content
typedef struct s_object
{
	unsigned int	type;
	t_vec3			coor;
	t_vec3			color;
	union
	{
		t_vec3		orientation;
		t_vec3		light_color;
	};
	union
	{
		float		ambient_ratio;
		float		light_brightness;
		float		camera_fov;
		float		radius;
	};
	float			height;
	t_material		material;
	int				hide;
}	t_object;

// MLX Metal buffer width may more than requested
// eg request 800px width, but actual width is 832px
// width = line_length / (bits_per_pixel / 8)
// use t_image.px (update by int) (support both little(x86) and big endian)
// t_image.c (update by char), either litte(x86) or big endian works, NOT BOTH
typedef struct s_image
{
	int		width;
	int		height;
	void	*ptr;
	union
	{
		void	*addr;
		char	*c;
		int		*px;
	};
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_image;

// a scene has only 1 ambient, 1 camera, 1light
// a scene has multiple sphere/plane/cylinder objects (malloc & linkedlist)
// ++last_updated when user inputs, so render() may refresh accordingly
typedef struct s_app
{
	struct
	{
		const char		*scene_file;
		t_list			*objects;
		t_list			*selected_object;
		int				object_count[OBJECT_TYPE_COUNT];
		t_object		*object[OBJECT_TYPE_COUNT];
	};
	struct
	{
		void			*mlx_ptr;
		void			*win_ptr;
		t_image			image;
	};
	unsigned int	invalidated;
	int				features;
	int				keypressed;
}	t_app;

#endif
