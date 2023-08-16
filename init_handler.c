/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauvicto <pauvicto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 18:51:44 by pauvicto          #+#    #+#             */
/*   Updated: 2023/08/16 20:57:48 by pauvicto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_data(t_data *data, int argc, char *argv[])
{
	data->start_time = 0;
	data->stop_condition = 0;
	data->max_ate = 0;
	data->philo_amount = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->eat_count_max = 0;
	data->philo = malloc(sizeof(t_philo) * data->philo_amount);
	if (argc == 6)
		data->eat_count_max = ft_atoi(argv[5]);
	if (argc == 6 && data->eat_count_max == 0)
		return (data->error = INVALID_PARAMETER_FORMAT);
	if (data->philo_amount < 1 || data->time_to_die < 0 || data->time_to_eat < 0
		|| data->time_to_sleep < 0 || data->eat_count_max < 0)
		return (data->error = INVALID_PARAMETER_FORMAT);
	if (data->philo == NULL)
		return (data->error = PHILO_MALLOC_ERROR);
	return (0);
}

int	init_mutexes(t_data *data)
{
	if (pthread_mutex_init(&data->write_mutex, NULL) != 0)
		return (data->error = INIT_MUTEX_ERROR);
	if (pthread_mutex_init(&data->meal_mutex, NULL) != 0)
		return (data->error = INIT_MUTEX_ERROR);
	if (pthread_mutex_init(&data->dead_mutex, NULL) != 0)
		return (data->error = INIT_MUTEX_ERROR);
	if (pthread_mutex_init(&data->stop_mutex, NULL) != 0)
		return (data->error = INIT_MUTEX_ERROR);
	return (0);
}

int	init_philos(t_data *data)
{
	int	i;

	data->start_time = ft_get_time();
	i = -1;
	while (++i < data->philo_amount)
	{
		data->philo[i].data = data;
		data->philo[i].ate_times = 0;
		data->philo[i].last_ate = 0;
		data->philo[i].pos = i + 1;
	}
	forks_handler(data);
	if (threads_maker(data) != 0)
		return (data->error = INIT_PHILOS_ERROR);
	i = -1;
	while (++i < data->philo_amount)
	{
		if (pthread_join(data->philo[i].thread_id, NULL) != 0)
			return (data->error = INIT_PHILOS_ERROR);
	}
	return (0);
}

int	init_handler(t_data *data, int argc, char *argv[])
{
	if (init_data(data, argc, argv) != 0)
		return (error_handler(data));
	if (init_mutexes(data) != 0)
		return (error_handler(data));
	if (init_philos(data) != 0)
		return (error_handler(data));
	return (0);
}
