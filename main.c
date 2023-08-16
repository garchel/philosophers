/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauvicto <pauvicto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 18:51:39 by pauvicto          #+#    #+#             */
/*   Updated: 2023/08/16 20:56:59 by pauvicto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	verify_digit_signal(char c)
{
	if ((c >= '0' && c <= '9') || (c == '-' && c == '+'))
		return (true);
	return (false);
}

bool	validate_digits(char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (verify_digit_signal(argv[i][j]) == false)
				return (false);
			j += 1;
		}
		i += 1;
	}
	return (true);
}

int	validate_parameters(t_data *data, int argc, char *argv[])
{
	int	i;

	i = 1;
	if (argc != 5 && argc != 6)
		return (data->error = INVALID_PARAMETER_QUANT);
	while (i < argc)
	{
		if (validate_digits(&argv[i]) == false)
			return (data->error = INVALID_PARAMETER_FORMAT);
		i++;
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (validate_parameters(&data, argc, argv) != 0)
		return (error_handler(&data));
	if (init_handler(&data, argc, argv) != 0)
		return (error_handler(&data));
	free_handler(&data);
}
