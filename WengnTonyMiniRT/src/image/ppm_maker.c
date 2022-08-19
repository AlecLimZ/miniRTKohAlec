/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppm_maker.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 15:40:36 by hloke             #+#    #+#             */
/*   Updated: 2022/06/22 17:05:16 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "image.h"

static int	ft_ppm_header(
	const char *pathname, char *type, size_t row, size_t col)
{
	int	fd;

	fd = open(pathname, O_CREAT | O_TRUNC | O_WRONLY, S_IWUSR);
	if (fd == -1)
		ft_perror("Cannot create ppm file", 0);
	ft_putendl_fd(type, fd);
	ft_putnbr_fd(col, fd);
	ft_putstr_fd(" ", fd);
	ft_putnbr_fd(row, fd);
	ft_putstr_fd("\n", fd);
	ft_putnbr_fd(255, fd);
	ft_putstr_fd("\n", fd);
	return (fd);
}

/* Converts a t_img8 image to a ppm P3 format. */
int	ft_image8_2_ppm3(t_img8 *img, const char *pathname)
{
	int		fd;
	size_t	i;

	fd = ft_ppm_header(pathname, "P3", img->row, img->col);
	if (fd == -1)
		return (0);
	i = -1;
	while (++i < img->row * img->col * 3)
	{
		ft_putnbr_fd(img->data[i], fd);
		if (i % 3 != 2)
			ft_putchar_fd(' ', fd);
		else
			ft_putchar_fd('\n', fd);
	}
	close(fd);
	return (1);
}

/* Converts a t_img8 image to a ppm P6 format. */
int	ft_image8_2_ppm6(t_img8 *img, const char *pathname)
{
	int		fd;

	fd = ft_ppm_header(pathname, "P6", img->row, img->col);
	if (fd == -1)
		return (0);
	write(fd, img->data, img->row * img->col * 3);
	ft_putchar_fd('\n', fd);
	close(fd);
	return (1);
}

/* Convert a t_img image to ppm of a given type */
int	ft_image_2_ppm(t_img *img, const char *pathname, int type)
{
	t_img8	*img_bit;
	int		retval;

	if ((type == 3 || type == 6) == 0)
		return (0);
	img_bit = ft_image_2_image8(img);
	if (type == 3)
		retval = ft_image8_2_ppm3(img_bit, pathname);
	else
		retval = ft_image8_2_ppm6(img_bit, pathname);
	ft_image8_del(img_bit);
	return (retval);
}
