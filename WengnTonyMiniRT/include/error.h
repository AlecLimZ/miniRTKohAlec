/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 11:11:43 by weng              #+#    #+#             */
/*   Updated: 2022/06/22 16:55:40 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

// ft_error.c
void	ft_perror(const char *s, int n);

#endif
