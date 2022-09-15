/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Koh <Koh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:05:48 by Koh               #+#    #+#             */
/*   Updated: 2022/09/15 14:06:01 by Koh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	main(int argc, char **argv)
{
	t_app		app;

	app = (t_app){};
	if (argc != 2)
		app_exit(&app, "Require 1 rt file");
	parse_file(argv[1], &app);
	printf("lstsize %d\n", ft_lstsize(app.objects));
	app_exit(&app, NULL);
}
