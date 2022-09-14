/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ansi_colors.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoh <skoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 23:01:39 by skoh              #+#    #+#             */
/*   Updated: 2021/11/26 23:13:02 by skoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// https://github.com/tomsik68/ansi_colors
// https://github.com/tomsik68/ansi_colors/blob/master/test.c

#ifndef ANSI_COLORS_H
# define ANSI_COLORS_H

# ifdef NOCOLOR

#  define BOLD ""
#  define WEAK ""
#  define HIGHLIGHT ""
#  define UNDERLINE ""
#  define BLACK ""
#  define DARK_RED ""
#  define DARK_GREEN ""
#  define DARK_YELLOW ""
#  define DARK_BLUE ""
#  define DARK_PINK ""
#  define DARK_CYAN ""
#  define BLACK_BG ""
#  define DARK_RED_BG ""
#  define DARK_GREEN_BG ""
#  define DARK_YELLOW_BG ""
#  define DARK_BLUE_BG ""
#  define DARK_PINK_BG ""
#  define DARK_CYAN_BG ""
#  define GRAY ""
#  define LIGHT_RED ""
#  define LIGHT_GREEN ""
#  define LIGHT_YELLOW ""
#  define LIGHT_BLUE ""
#  define LIGHT_PINK ""
#  define LIGHT_CYAN ""
#  define LIGHT_GRAY ""
#  define GRAY_BG ""
#  define LIGHT_RED_BG ""
#  define LIGHT_GREEN_BG ""
#  define LIGHT_YELLOW_BG ""
#  define LIGHT_BLUE_BG ""
#  define LIGHT_PINK_BG ""
#  define LIGHT_CYAN_BG ""
#  define LIGHT_GRAY_BG ""
#  define RESET ""

# else

#  define BOLD "\033[1m"
#  define WEAK "\033[2m"
#  define HIGHLIGHT "\033[3m"
#  define UNDERLINE "\033[4m"
#  define BLACK "\033[30m"
#  define DARK_RED "\033[31m"
#  define DARK_GREEN "\033[32m"
#  define DARK_YELLOW "\033[33m"
#  define DARK_BLUE "\033[34m"
#  define DARK_PINK "\033[35m"
#  define DARK_CYAN "\033[36m"
#  define BLACK_BG "\033[40m"
#  define DARK_RED_BG "\033[41m"
#  define DARK_GREEN_BG "\033[42m"
#  define DARK_YELLOW_BG "\033[43m"
#  define DARK_BLUE_BG "\033[44m"
#  define DARK_PINK_BG "\033[45m"
#  define DARK_CYAN_BG "\033[46m"
#  define GRAY "\033[90m"
#  define LIGHT_RED "\033[91m"
#  define LIGHT_GREEN "\033[92m"
#  define LIGHT_YELLOW "\033[93m"
#  define LIGHT_BLUE "\033[94m"
#  define LIGHT_PINK "\033[95m"
#  define LIGHT_CYAN "\033[96m"
#  define LIGHT_GRAY "\033[97m"
#  define GRAY_BG "\033[100m"
#  define LIGHT_RED_BG "\033[101m"
#  define LIGHT_GREEN_BG "\033[102m"
#  define LIGHT_YELLOW_BG "\033[103m"
#  define LIGHT_BLUE_BG "\033[104m"
#  define LIGHT_PINK_BG "\033[105m"
#  define LIGHT_CYAN_BG "\033[106m"
#  define LIGHT_GRAY_BG "\033[107m"
#  define RESET "\033[m"

# endif

# define LF "\n"

#endif
