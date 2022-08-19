/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 08:55:51 by hloke             #+#    #+#             */
/*   Updated: 2022/06/23 23:32:40 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_H
# define DISPLAY_H

# include "element.h"
# include "image.h"
# include "minirt.h"
# include "mlx.h"
# include "parse.h"

/* 
 * MAC version
 * Keycodes for esc, qwerty keyboard, arrow keys and number pads 
 */
enum e_keycode
{
	MAC_ESC = 53,
	MAC_Q = 12,
	MAC_W = 13,
	MAC_E = 14,
	MAC_R = 15,
	MAC_T = 17,
	MAC_Y = 16,
	MAC_U = 32,
	MAC_I = 34,
	MAC_O = 31,
	MAC_P = 35,
	MAC_A = 0,
	MAC_S = 1,
	MAC_D = 2,
	MAC_F = 3,
	MAC_G = 5,
	MAC_H = 4,
	MAC_J = 38,
	MAC_K = 40,
	MAC_L = 37,
	MAC_Z = 6,
	MAC_X = 7,
	MAC_C = 8,
	MAC_V = 9,
	MAC_B = 11,
	MAC_N = 45,
	MAC_M = 46,
	MAC_UP = 126,
	MAC_DOWN = 125,
	MAC_LEFT = 123,
	MAC_RIGHT = 124,
	MAC_ONE = 18,
	MAC_TWO = 19,
	MAC_THREE = 20,
	MAC_FOUR = 21,
	MAC_FIVE = 23,
	MAC_SIX = 22,
	MAC_SEVEN = 26,
	MAC_EIGHT = 28,
	MAC_NINE = 25,
	WIN_ESC = 65307,
	WIN_Q = 113,
	WIN_W = 119,
	WIN_E = 101,
	WIN_R = 114,
	WIN_T = 116,
	WIN_Y = 121,
	WIN_U = 117,
	WIN_I = 105,
	WIN_O = 111,
	WIN_P = 112,
	WIN_A = 97,
	WIN_S = 115,
	WIN_D = 100,
	WIN_F = 102,
	WIN_G = 103,
	WIN_H = 104,
	WIN_J = 106,
	WIN_K = 107,
	WIN_L = 108,
	WIN_Z = 122,
	WIN_X = 120,
	WIN_C = 99,
	WIN_V = 118,
	WIN_B = 98,
	WIN_N = 110,
	WIN_M = 109,
	WIN_UP = 65362,
	WIN_DOWN = 65364,
	WIN_LEFT = 65361,
	WIN_RIGHT = 65363,
	WIN_PAGEUP = 65365,
	WIN_PAGEDOWN = 65366,
	WIN_ONE = 65436,
	WIN_TWO = 65433,
	WIN_THREE = 65435,
	WIN_FOUR = 65430,
	WIN_FIVE = 65437,
	WIN_SIX = 65432,
	WIN_SEVEN = 65429,
	WIN_EIGHT = 65431,
	WIN_NINE = 65434
};

enum e_select
{
	CAMERA,
	LIGHT,
	OBJECT,
};

/* structure for minilibx image */
typedef struct s_image
{
	void	*mlx_ptr;
	void	*img_ptr;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_length;
	int		endian;
}	t_image;

/* structure for minilibx variables. */
typedef struct s_mlx
{
	int		width;
	int		height;
	int		select;
	void	*mlx_ptr;
	void	*win_ptr;
	t_light	*ambient;
	t_list	*lights;
	t_list	*objs;
	t_cam	*cam;
	t_img8	*img8;
	t_image	*image;
	t_list	*obj_o;
	t_list	*light_o;
}	t_mlx;

//* ft_cam_transform.c
void	ft_cam_rotate_x(t_cam *cam, double theta);
void	ft_cam_rotate_y(t_cam *cam, double theta);
void	ft_cam_rotate_z(t_cam *cam, double theta);
void	ft_cam_translate(t_cam *cam, double dx, double dy, double dz);

//* ft_display.c
void	ft_display_update(t_mlx *mlx, int rerender);

//* ft_draw.c
void	ft_draw_image(t_image *image, t_img *img8);

//* ft_light_transform.c
void	ft_light_rotate_x(t_light *light, double theta);
void	ft_light_rotate_y(t_light *light, double theta);
void	ft_light_rotate_z(t_light *light, double theta);
void	ft_light_translate(t_light *light, double dx, double dy, double dz);

//* ft_mlx_image.c
t_image	*ft_mlx_image_new(void *mlx_ptr, int width, int height);
void	ft_mlx_image_del(t_image *image);
void	ft_mlx_image_put(t_mlx *mlx, t_image *image, int x, int y);

//* ft_mlx_key.c
int		ft_mlx_key(int keycode, t_mlx *mlx);

//* ft_mlx.c
t_mlx	*ft_mlx_new(int width, int height);
void	ft_mlx_init(t_mlx *mlx);
int		ft_mlx_del(t_mlx *mlx);

//* ft_obj_transform.c
void	ft_obj_rotate_x(t_obj *obj, double theta);
void	ft_obj_rotate_y(t_obj *obj, double theta);
void	ft_obj_rotate_z(t_obj *obj, double theta);
void	ft_obj_translate(t_obj *obj, double dx, double dy, double dz);

#endif
