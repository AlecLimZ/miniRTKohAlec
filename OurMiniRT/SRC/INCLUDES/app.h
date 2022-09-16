/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Koh <Koh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:01:46 by Koh               #+#    #+#             */
/*   Updated: 2022/09/16 17:57:06 by Koh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef APP_H
# define APP_H

# include "miniRT.h"

void	app_exit(t_app *app, const char *error);
int		if_errno_exit(int ret, t_app *app);
void	*if_null_exit(void *p, t_app *app);

#endif
