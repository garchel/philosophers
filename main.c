/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauvicto <pauvicto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 18:51:39 by pauvicto          #+#    #+#             */
/*   Updated: 2023/08/15 01:54:42 by pauvicto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int validate_parameters(t_data *data, int argc, char* argv[])
{
	int i;

	i = 1;
	if ( argc != 5 && argc != 6)
		return (data->error = INVALID_PARAMETER_AMOUNT);
	while (i < argc)
	{
		if (is_all_digits(&argv[i]) == false)
			return (data->error = INVALID_PARAMETER_TYPE);
		i++;
	}
	return (0);
}

int main(int argc, char* argv[])
{
	t_data data;

	//memset(&data, 0, sizeof(t_data));
	printf("Validando Parametros\n");
	if (validate_parameters(&data, argc, argv) != 0)
		return (error_handler(&data));
	printf("Init Handler \n");
	if (init_handler(&data, argc, argv) != 0)
		return (error_handler(&data));
	free_handler(&data);
}