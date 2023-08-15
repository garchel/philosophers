/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauvicto <pauvicto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 19:18:09 by pauvicto          #+#    #+#             */
/*   Updated: 2023/08/15 00:55:17 by pauvicto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Invalid Parameter Number
// Invalid Parameter Type

#include "philosophers.h"

void free_handler(t_data *data)
{
    int i;

    i = -1;
    while (i++ < data->philo_amount)
    {
            pthread_mutex_destroy(&data->philo[i].left_fork);
            pthread_mutex_destroy(data->philo[i].right_fork);
    }
	pthread_mutex_destroy(&data->meal_mutex);
	pthread_mutex_destroy(&data->write_mutex);
	pthread_mutex_destroy(&data->dead_mutex);
    if (data->philo)
        free(data->philo);
    if (data)
        free(data);
}

int error_handler(t_data *data)
{
    if (data->error == 1)
    {
        printf("\033[1;31mError: Invalid Parameter Quantity\033[0m\n");
    }
    if (data->error == 2)
    {
        printf("\033[1;31mError: Invalid Parameter Type\033[0m\n");
    }
    if (data->error == 3)
    {
        printf("\033[1;31mError: Philo Malloc Error\033[0m\n");
    }
    if (data->error == 4)
    {
        printf("\033[1;31mError: Init Data Error\033[0m\n");
    }
    if (data->error == 5)
    {
        printf("\033[1;31mError: Init Mutex Error\033[0m\n");
    }
    if (data->error == 6)
    {
        printf("\033[1;31mError: Init Philos Error\033[0m\n");
    }
    free_handler(data);
	return (0);
}