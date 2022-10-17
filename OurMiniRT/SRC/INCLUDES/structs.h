/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Koh <Koh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:12:26 by Koh               #+#    #+#             */
/*   Updated: 2022/10/17 18:34:12 by leng-chu         ###   ########.fr       */
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
	double	e[3];
	double	rgb[3];
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

// tinyraytracer: albedo[diffuse, specular, reflect]
typedef struct s_material {
	float	albedo[3];
	float	specular_exponent;
	t_vec3	diffuse_color;
}	t_material;

// all raytracing objects as linked-list content
typedef struct s_object
{
	int			type;
	t_xyz		coor;
	t_rgb		color;
	t_xyz		orientation;
	t_xyz		normal;
	double		radius;
	t_material	material;
	union
	{
		double	camera_fov;
		double	height;
	};
}	t_object;

// MLX Metal buffer width may more than requested
// eg request 800px width, but actual width is 832px
// width = line_length / (bits_per_pixel / 8)
// use t_image.px (update by int) (support both little(x86) and big endian)
// t_image.c (update by char), either litte(x86) or big endian works, NOT BOTH
typedef struct s_image
{
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
	int		width;
}	t_image;

// a scene has only 1 ambient, 1 camera, 1light
// a scene has multiple sphere/plane/cylinder objects (malloc & linkedlist)
// ++last_updated when user inputs, so render() may refresh accordingly
typedef struct s_app
{
	unsigned int	last_updated;
	int				width;
	int				height;
	t_list			*objects;
	t_list			*selected_object;
	t_object		*ambient;
	t_object		*camera;
	int				ambient_count;
	int				camera_count;
	int				light_count;
	void			*mlx_ptr;
	void			*win_ptr;
	t_image			image;
	int				render_mode;
}	t_app;

#endif

// typedef union s_wh
// {
// 	int	e[2];
// 	struct
// 	{
// 		int	width;
// 		int	height;
// 	};
// 	struct
// 	{
// 		int	w;
// 		int	h;
// 	};
// 	struct
// 	{
// 		int	col;
// 		int	row;
// 	};
// 	struct
// 	{
// 		int	c;
// 		int	r;
// 	};
// 	struct
// 	{
// 		int	x;
// 		int	y;
// 	};
// }	t_wh;

// only 1 ambient-light allowed (check "is_configured") 
// typedef struct s_ambient
// {
// 	double	ratio;
// 	t_rgb	color;
// 	int		is_configured;
// }	t_ambient;

// only 1 camera allowed (check "is_configured") 
// typedef struct s_camera
// {
// 	double	fov;
// 	union
// 	{
// 		t_xyz	coor;
// 		t_xyz	origin;
// 	};
// 	t_xyz	orientation;
// 	int		is_configured;
// }	t_camera;

// only 1 light allowed (check "is_configured") 
// typedef struct s_light
// {
// 	double	brightness;
// 	t_xyz	coor;
// 	t_rgb	color;
// 	int		is_configured;
// }	t_light;
