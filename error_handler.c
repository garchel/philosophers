/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauvicto <pauvicto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 19:18:09 by pauvicto          #+#    #+#             */
/*   Updated: 2023/08/16 19:54:23 by pauvicto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_handler(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_amount)
	{
		pthread_mutex_destroy(&data->philo[i].left_fork);
		pthread_mutex_destroy(data->philo[i].right_fork);
	}
	pthread_mutex_destroy(&data->meal_mutex);
	pthread_mutex_destroy(&data->write_mutex);
	pthread_mutex_destroy(&data->dead_mutex);
	pthread_mutex_destroy(&data->stop_mutex);
	free(data->philo);
}

int	error_handler(t_data *data)
{
	if (data->error == INVALID_PARAMETER_QUANT)
	{
		printf("\033[1;31mError: Invalid Parameter Quantity\033[0m\n");
	}
	if (data->error == INVALID_PARAMETER_FORMAT)
	{
		printf("\033[1;31mError: Invalid Parameter Format\033[0m\n");
	}
	if (data->error == PHILO_MALLOC_ERROR)
	{
		printf("\033[1;31mError: Philo Malloc Error\033[0m\n");
	}
	if (data->error == INIT_MUTEX_ERROR)
	{
		printf("\033[1;31mError: Init Mutex Error\033[0m\n");
	}
	if (data->error == INIT_PHILOS_ERROR)
	{
		printf("\033[1;31mError: Init Philos Error\033[0m\n");
	}
	return (0);
}
