/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppm_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 15:35:27 by weng              #+#    #+#             */
/*   Updated: 2022/06/22 17:05:16 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "image.h"

/* Open a file as a file stream */
static FILE	*ft_fopen(const char *pathname, const char *mode)
{
	FILE	*stream;

	stream = fopen(pathname, mode);
	if (stream == NULL)
		ft_perror("cannot read a ppm file", 0);
	return (stream);
}

/* Reads a simplified version of the ppm file and returns a t_img8 result. 
 * Currently, only P6 is supported.
 *
 * The header of the file must be as such
 * P6
 * comment (optional)
 * col row
 * 255
 * data
 */
static t_img8	*ft_ppm_2_image8(FILE *stream)
{
	int		retval;
	char	type[3];
	size_t	size[3];
	char	*data;
	t_img8	*img;

	retval = fscanf(
			stream, "%s\n%ld %ld\n%ld\n", type, &size[0], &size[1], &size[2]);
	if (retval == EOF || retval == 0
		|| ft_strcmp("P6", type) != 0 || size[2] != 255)
		ft_perror("Invalid ppm header. Expect P6\\ncol row\\n255.\\n", EINVAL);
	data = ft_calloc(sizeof(unsigned char), (size[0] * size[1] * 3) + 1);
	if (data == NULL)
		ft_perror("ft_ppm_2_image: failed memory allocation", 0);
	size[2] = size[0] * size[1] * 3;
	fread(data, size[2] + 1, sizeof(char), stream);
	if (data == NULL)
		ft_perror("ft_ppm_2_image: can't read data from image file", 0);
	img = ft_image8_new(size[1], size[0]);
	while (size[2]-- > 0)
		img->data[size[2]] = (unsigned char) data[size[2]];
	fclose(stream);
	free(data);
	return (img);
}

/* Reads a simplified version of the ppm file and returns a t_img result. 
 * Currently, only P6 is supported.
 *
 * The header of the file must be as such
 * P6
 * col row
 * 255
 * data
 */
t_img	*ft_ppm_2_image(const char *pathname)
{
	FILE	*stream;
	t_img8	*img_bit;
	t_img	*img;

	stream = ft_fopen(pathname, "r");
	img_bit = ft_ppm_2_image8(stream);
	img = ft_image8_2_image(img_bit);
	ft_image8_del(img_bit);
	return (img);
}
