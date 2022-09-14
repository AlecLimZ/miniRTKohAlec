/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Koh <Koh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 13:10:51 by Koh               #+#    #+#             */
/*   Updated: 2022/09/14 16:24:37 by Koh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// todo 
// 1) function converts string to double
// 2) struct for storage
// 3) parse functions for sphere, cylinder, plane
// 4) refactor and split files
// 5) unit test?

#include <fcntl.h>
#include "libft/libft.h"
#include "get_next_line.h"

#define MIN_COOR -999
#define MAX_COOR 999

#include <stdlib.h>
#include <stdio.h>
double	parse_double(char **a)
{
	const double d = strtod(a[0], NULL);
	
	write(1, a[0], a[1] - a[0]);
	printf(" to %f\n", d);
	return (d);
}


int	ft_isspace(int c)
{
	return (c == ' ' || ('\t' <= c && c <= '\r'));
}

int	ft_iscomma(int c)
{
	return (c == ',');
}

int	ft_isminus(int c)
{
	return (c == '-');
}

int	ft_isdot(int c)
{
	return (c == '.');
}

int	start_with(char *s, char c)
{
	while (*s && ft_isspace(*s))
		++s;
	return (*s == c);
}

int	if_error_exit(int ret)
{
	if (ret < 0)
	{
		perror("Error");
		exit(1);
	}
	return (ret);
}

/* f = ft_isdigit/alpha/space/comma */
int	pull_str(char **s, int (*f)(int), char **begin, char **end)
{
	const char	*s_ = *s;

	if (begin)
		*begin = *s;
	while (**s && f(**s))
		++*s;
	if (end)
		*end = *s;
	return (*s - s_);
}

int	trim_str(char **s, int (*f)(int))
{
	return (pull_str(s, f, NULL, NULL));
}

int	pull_nbr(char **line, double *d, double min, double max)
{
	char	*s[2];

	if (pull_str(line, ft_isminus, s + 0, NULL) <= 1
		&& trim_str(line, ft_isdigit) >= 1
		&& trim_str(line, ft_isdot) <= 1
		&& pull_str(line, ft_isdigit, NULL, s + 1) >= 0
	)
	{
		*d = parse_double(s);
		return (*d >= min && *d <= max);
	}
	return (0);
}

///////////////////////////////////////////////////////////////////////////////

int	parse_ambient(char *line)
{
	double	d;

	if (trim_str(&line, ft_isalpha) == 1
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_nbr(&line, &d, 0, 1) == 1
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_nbr(&line, &d, 0, 255) == 1
		&& trim_str(&line, ft_iscomma) == 1
		&& pull_nbr(&line, &d, 0, 255) == 1
		&& trim_str(&line, ft_iscomma) == 1
		&& pull_nbr(&line, &d, 0, 255) == 1
		&& trim_str(&line, ft_isspace) >= 0
		&& (*line == '#' || *line == '\0')
	)
	{
		return (1);
	}
	ft_putendl_fd("Error: Invalid Ambient", 2);
	return (0);
}

int	parse_camera(char *line)
{
	double	d;

	if (trim_str(&line, ft_isalpha) == 1
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_nbr(&line, &d, MIN_COOR, MAX_COOR) == 1
		&& trim_str(&line, ft_iscomma) == 1
		&& pull_nbr(&line, &d, MIN_COOR, MAX_COOR) == 1
		&& trim_str(&line, ft_iscomma) == 1
		&& pull_nbr(&line, &d, MIN_COOR, MAX_COOR) == 1
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_nbr(&line, &d, -1, 1) == 1
		&& trim_str(&line, ft_iscomma) == 1
		&& pull_nbr(&line, &d, -1, 1) == 1
		&& trim_str(&line, ft_iscomma) == 1
		&& pull_nbr(&line, &d, -1, 1) == 1
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_nbr(&line, &d, 0, 180) == 1
		&& trim_str(&line, ft_isspace) >= 0
		&& (*line == '#' || *line == '\0')
	)
	{
		return (1);
	}
	ft_putendl_fd("Error: Invalid Camera", 2);
	return (0);
}

int	parse_light(char *line)
{
	double	d;

	if (trim_str(&line, ft_isalpha) == 1
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_nbr(&line, &d, MIN_COOR, MAX_COOR) == 1
		&& trim_str(&line, ft_iscomma) == 1
		&& pull_nbr(&line, &d, MIN_COOR, MAX_COOR) == 1
		&& trim_str(&line, ft_iscomma) == 1
		&& pull_nbr(&line, &d, MIN_COOR, MAX_COOR) == 1
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_nbr(&line, &d, 0, 1) == 1
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_nbr(&line, &d, 0, 255) == 1
		&& trim_str(&line, ft_iscomma) == 1
		&& pull_nbr(&line, &d, 0, 255) == 1
		&& trim_str(&line, ft_iscomma) == 1
		&& pull_nbr(&line, &d, 0, 255) == 1
		&& trim_str(&line, ft_isspace) >= 0
		&& (*line == '#' || *line == '\0')
	)
	{
		return (1);
	}
	ft_putendl_fd("Error: Invalid Camera", 2);
	return (0);
}

/////////////////////////////////////////////////////////////////////////////

static void	parse_object(char *line, size_t len)
{
	int			i;
	const void	*f[] = {
		"A", &parse_ambient,
		"C", &parse_camera,
		"L", &parse_light,
		// "sp", &parse_sphere,
		// "pl", &parse_plane,
		// "cy", &parse_cylinder,
		NULL,
	};

	i = 0;
	while (f[i] && (ft_strlen(f[i]) != len || ft_strncmp(line, f[i], len) != 0))
		i += 2;
	if (f[i] && ((int (*)(char *))f[i + 1])(line))
		ft_putendl_fd(line, 1);
}

static void	parse_line(char *line)
{
	char	*begin;
	char	*end;

	trim_str(&line, ft_isspace);
	if (*line == '#' || *line == '\0')
		return ;
	if (pull_str(&line, ft_isalpha, &begin, &end) > 0
		&& trim_str(&line, ft_isspace) > 0)
		parse_object(begin, end - begin);
	else
		ft_putendl_fd("Error: Invalid format", 2);
}

void	parse_file(char *fp)
{
	char		*line;
	const int	fd = if_error_exit(open(fp, 0));

	while (get_next_line(fd, &line))
	{
		parse_line(line);
		free(line);
		line = NULL;
	}
	free(line);
	close(fd);
}

//////////////////////////////////////////////////////////////////////////

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_putendl_fd("Error: Require 1 rt file", 2);
		return (1);
	}
	parse_file(argv[1]);
	return (0);
}

/*
	return (0);
	char *s[10] = {};
	char **ss = s;
	char *a = "abCDE123";
	if (start_with("   		   # ", '#'))
		ft_putendl_fd("is comment", 1);
	if (start_with("   		   c ", 'C'))
		ft_putendl_fd("is C", 1);

	ft_putnbr_fd(trim_str(&a, ft_isalpha, s + 0, s + 1), 1);
	ft_putnbr_fd(trim_str(&a, ft_isdigit, s + 2, s + 3), 1);
	ft_putchar_fd('\n', 1);
	for (int i = 0; i < 4; i+=2)
	{
		while (s[i] < s[i+1])
			ft_putchar_fd(*s[i]++, 1);
		ft_putendl_fd("", 1);
	}
*/
