/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 10:57:59 by weng              #+#    #+#             */
/*   Updated: 2021/11/29 12:02:23 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**free_if_error(int argc, char **argv, char *word)
{
	while (argc-- > 0)
		free(argv[argc]);
	free(argv);
	free(word);
	return (NULL);
}

static char	**ft_split_aux(char *s, char c, int argc, char **argv)
{
	int		len;
	char	*end;
	char	*word;
	char	**argv_new;

	while (*s == c && c != '\0')
		s++;
	if (*s == '\0')
		return (argv);
	end = ft_strchr(s, c);
	if (end != NULL)
		len = end - s;
	else
		len = ft_strlen(s);
	word = ft_substr(s, 0, len);
	argv_new = ft_calloc(argc + 2, sizeof(char *));
	if (word == NULL || argv_new == NULL)
		return (free_if_error(argc, argv, word));
	ft_memmove(argv_new, argv, sizeof(char *) * argc);
	argv_new[argc] = word;
	free(argv);
	return (ft_split_aux(s + len, c, argc + 1, argv_new));
}

/*
Allocates (with malloc(3)) and returns an array of strings obtained by
splitting 's' using the character 'c' as a delimiter. The array must be
ended by a NULL pointer.

There cannot be any empty strings in the returned array,
i.e. consecutive separators are disregarded.
*/
char	**ft_split(char const *s, char c)
{
	char	**argv;

	argv = ft_calloc(1, sizeof(char *));
	if (argv != NULL)
		argv = ft_split_aux((char *) s, c, 0, argv);
	return (argv);
}
