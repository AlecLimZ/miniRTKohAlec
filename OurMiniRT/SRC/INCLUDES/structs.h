/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Koh <Koh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:12:26 by Koh               #+#    #+#             */
/*   Updated: 2022/10/18 11:25:20 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# define MIN_COOR -999
# define MAX_COOR 999
# define PI 3.14159

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

enum e_render_mode
{
	DEFAULT_RENDER,
	BY_DISTANCE,
	BY_NORMAL,
	BY_OBJECT,
	RENDER_MODE_END,
};

typedef union s_vec3
{
	float	e[3];
	float	rgb[3];
	struct
	{
		float	x;
		float	y;
		float	z;
	};
	struct
	{
		float	r;
		float	g;
		float	b;
	};
}	t_vec3;

typedef t_vec3	t_rgb;
typedef t_vec3	t_xyz;

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
	t_xyz			coor;
	t_rgb			color;
	union
	{
		t_xyz		orientation;
		t_rgb		light_color;
	};
	union
	{
		float		param1;
		float		ambient_ratio;
		float		light_brightness;
		float		camera_fov;
		float		radius;
	};
	union
	{
		float		param2;
		float		height;
	};
	t_material		material;
}	t_object;

typedef struct s_object_params
{
	float	param1_step;
	float	param1_min;
	float	param1_max;
	float	param2_step;
	float	param2_min;
	float	param2_max;
}			t_object_params;

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
		t_object		*object_ptr[OBJECT_TYPE_COUNT];
	};
	struct
	{
		void			*mlx_ptr;
		void			*win_ptr;
		t_image			image;
	};
	struct
	{
		unsigned int	last_updated;
		int				render_mode;
		int				use_gamma_correction;
		unsigned int	mini;
	};
}	t_app;

#endif
