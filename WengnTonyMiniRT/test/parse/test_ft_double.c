/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_double.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 16:32:50 by weng              #+#    #+#             */
/*   Updated: 2022/06/11 11:11:11 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	test_atof(void)
{
	const char	input[][100] = {
		"-1",
		"+1",
		"999",
		"-999",
		"0.0",
		"-0.0",
		"0.1",
		"-0.1",
		"9.90000000",
		"-9.90000000",
		"9.900000500",
		"-9.900000500",
		"3.14159265359",
		"-3.14159265359",
		"2147483647.214748",
		"-2147483648.214748",
		"2147483647.00000000",
		"-2147483648.00000000",
		"2147483647.2147483647",
		"-2147483648.2147483648",
		"12345678901234567890",
		"1.23456789012345678901",
		"1.2345678901234e-012",
		"1.2345678901234e012",
		"1.2345678901234e+012",
		"1.2345678901234e123",
		"1.2345678901234e-500",
		"1.2345678901234e+0500",
		"1.2345678901234e500"};
	int			n;
	double		target;
	double		val;
	int			retval;

	retval = 1;
	n = sizeof(input) / sizeof(input[0]);
	while (n-- > 0)
	{
		target = atof(input[n]);
		val = ft_atof(input[n]);
		if (eq_double(target, val) == 0)
		{
			printf("ft_atof: Error for input %s\n", input[n]);
			printf("   atof output = %.16e\n", target);
			printf("ft_atof output = %.16e\n\n", val);
			retval = 0;
		}
	}
	if (retval == 1)
		printf("ft_atof: OK\n");
}

void	test_check_vector(void)
{
	t_vec	*vec;

	vec = ft_parse_vector("0,100,200", 3, -1000, 1000);
	printf("ft_parse_vector: OK\n");
	ft_vec_del(vec);
}

void	test_check_vector_null(void)
{
	t_vec	*vec;

	vec = ft_parse_vector("", 0, 0, 0);
	if (vec != NULL)
		printf("ft_parse_vector NULL: Error!\n");
	else
		printf("ft_parse_vector NULL: OK\n");
	ft_vec_del(vec);
}

int	main(void)
{
	test_atof();
	test_check_vector();
	test_check_vector_null();
	return (0);
}
