/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_scene.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:05:48 by hloke             #+#    #+#             */
/*   Updated: 2022/06/22 17:05:16 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

/* Open a scene file that ends with .rt, and return the file descriptor. */
int	ft_open_scene(const char *scene)
{
	char	*ptr;
	int		fd;

	ptr = ft_strrchr(scene, '.');
	if (ptr == NULL || ft_strcmp(ptr, ".rt") != 0)
		ft_perror("Invalid input file format", EINVAL);
	fd = open(scene, O_RDONLY, 0);
	if (fd == -1)
		ft_perror("Scene file cannot be opened", 0);
	return (fd);
}

/* Parse one line of scene input file into an array, with 'c' as
 * delimiter. Continuous delimiter means some inputs are parsed as empty
 * string. The output from this function must eventually be freed. */
char	**ft_split_scene(const char *line, char c)
{
	char			**arr;
	char			*ptr;
	const size_t	max_arg = 7;
	size_t			i;

	arr = ft_calloc(sizeof(char *), max_arg + 1);
	if (arr == NULL)
		ft_perror("ft_split_scene cannot allocate memory", 0);
	i = 0;
	while (line && *line != '\0')
	{
		if (i == max_arg)
			ft_perror("Line in scene file is too long", ERANGE);
		ptr = ft_strchr(line, c);
		if (ptr != NULL)
			arr[i] = ft_substr(line, 0, ptr - line);
		else
			arr[i] = ft_strdup(line);
		line = ptr + (ptr != NULL);
		++i;
	}
	return (arr);
}

/* Strip trailing new line character, if any */
char	*ft_strip_newline(char *line)
{
	char	*ptr;

	if (line == NULL)
		return (NULL);
	ptr = ft_strchr(line, '\n');
	if (ptr != NULL)
		*ptr = '\0';
	return (line);
}

/* Parse one line of the scene file, and add to the approprite list. */
t_cam	*ft_parse_line(
	const char *line, t_light **ambient, t_list **lights, t_list **objs)
{
	char	**arr;

	arr = ft_split(line, ' ');
	if (ft_array_size(arr) == 0)
	{
		ft_array_del(arr, free);
		return (NULL);
	}
	else if (ft_strcmp(arr[0], "C") == 0)
		return (ft_parse_camera(arr));
	else if (ft_strcmp(arr[0], "A") == 0)
		*ambient = ft_parse_light_ambient(arr);
	else if (ft_strcmp(arr[0], "lp") == 0)
		ft_lstadd_back(lights, ft_lstnew(ft_parse_light_point(arr)));
	else if (ft_strcmp(arr[0], "ls") == 0)
		ft_lstadd_back(lights, ft_lstnew(ft_parse_light_spot(arr)));
	else
		ft_lstadd_back(objs, ft_lstnew(ft_parse_obj(arr)));
	return (NULL);
}

/* Parse a scene file and initialise all relevant objects. */
t_cam	*ft_parse_scene(
	const char *scene, t_light **ambient, t_list **lights, t_list **objs)
{
	int		fd;
	char	*line;
	t_cam	*cam;
	t_cam	*retval;

	cam = NULL;
	fd = ft_open_scene(scene);
	line = ft_strip_newline(get_next_line(fd));
	while (line != NULL)
	{
		if (*line != '#')
		{
			retval = ft_parse_line(line, ambient, lights, objs);
			if (retval != NULL)
				cam = retval;
		}
		free(line);
		line = ft_strip_newline(get_next_line(fd));
	}
	close(fd);
	if (cam == NULL)
		ft_perror("At least one camera is needed for a scene", EINVAL);
	return (cam);
}
