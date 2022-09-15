/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Koh <Koh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:01:46 by Koh               #+#    #+#             */
/*   Updated: 2022/09/15 14:14:06 by Koh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef APP_H
# define APP_H

# include "libft.h"
# include "structs.h"

void	app_exit(t_app *app, const char *error);
int		if_errno_exit(int ret, t_app *app);

#endif
