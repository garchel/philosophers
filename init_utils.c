/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauvicto <pauvicto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 20:57:26 by pauvicto          #+#    #+#             */
/*   Updated: 2023/08/16 20:58:41 by pauvicto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	forks_handler(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_amount)
	{
		pthread_mutex_init(&(data->philo[i].left_fork), NULL);
	}
	i = -1;
	while (++i < data->philo_amount)
	{
		if (i == data->philo_amount - 1)
			data->philo[i].right_fork = &data->philo[0].left_fork;
		else
			data->philo[i].right_fork = &data->philo[i + 1].left_fork;
	}
}

void	*philo_death_monitor(void *philosofer)
{
	t_philo	*philo;

	philo = (t_philo *)philosofer;
	while (!is_dead(philo, 0))
	{
		ft_usleep(philo->data->time_to_die + 1);
		pthread_mutex_lock(&philo->data->meal_mutex);
		pthread_mutex_lock(&philo->data->stop_mutex);
		if (!is_dead(philo, 0) && (ft_get_time() - philo->last_ate)
			>= (long)(philo->data->time_to_die))
		{
			philo_print(philo, " died\n");
			is_dead(philo, 1);
			pthread_mutex_unlock(&philo->data->meal_mutex);
			pthread_mutex_unlock(&philo->data->stop_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->data->meal_mutex);
		pthread_mutex_unlock(&philo->data->stop_mutex);
	}
	return (NULL);
}

int	threads_maker(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_amount)
	{
		if (pthread_create(&data->philo[i].thread_id, NULL, \
				&routine, &(data->philo[i])) != 0)
			return (data->error = INIT_PHILOS_ERROR);
		if (pthread_create(&data->philo[i].death_monitor_thread,
				NULL, philo_death_monitor, &(data->philo[i])) != 0)
			return (data->error = INIT_PHILOS_ERROR);
		pthread_detach(data->philo[i].death_monitor_thread);
	}
	return (0);
}
