/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauvicto <pauvicto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 18:51:33 by pauvicto          #+#    #+#             */
/*   Updated: 2023/08/16 20:00:34 by pauvicto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*philo_verify_death(void *phi)
{
	t_philo	*philo;

	philo = (t_philo *)phi;
	ft_usleep(philo->data->time_to_die + 1);
	pthread_mutex_lock(&philo->data->meal_mutex);
	pthread_mutex_lock(&philo->data->stop_mutex);
	if (!is_dead(philo, 0) && (ft_get_time() - philo->last_ate)
		>= (long)(philo->data->time_to_die))
	{
		pthread_mutex_unlock(&philo->data->meal_mutex);
		pthread_mutex_unlock(&philo->data->stop_mutex);
		philo_print(philo, " died\n");
		is_dead(philo, 1);
	}
	pthread_mutex_unlock(&philo->data->meal_mutex);
	pthread_mutex_unlock(&philo->data->stop_mutex);
	return (NULL);
}

void	philo_forks(t_philo *philo)
{
	pthread_mutex_lock(&(philo->left_fork));
	philo_print(philo, " has taken a fork\n");
	if (philo->data->philo_amount == 1)
	{
		ft_usleep(philo->data->time_to_die * 2);
		pthread_mutex_unlock(&(philo->left_fork));
		return ;
	}
	pthread_mutex_lock(philo->right_fork);
	philo_print(philo, " has taken a fork\n");
}

void	philo_eat(t_philo *philo)
{
	philo_print(philo, " is eating\n");
	pthread_mutex_lock(&(philo->data->meal_mutex));
	philo->last_ate = ft_get_time();
	philo->ate_times++;
	pthread_mutex_unlock(&(philo->data->meal_mutex));
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(&philo->left_fork);
	philo_print(philo, " is sleeping\n");
	ft_usleep(philo->data->time_to_sleep);
	philo_print(philo, " is thinking\n");
}

void	*routine(void *philosofer)
{
	t_philo		*philo;

	philo = (t_philo *)philosofer;
	while (!is_dead(philo, 0))
	{	
		philo_forks(philo);
		philo_eat(philo);
		if (philo->ate_times == philo->data->eat_count_max
			&& philo->data->eat_count_max != 0)
		{
			pthread_mutex_lock(&philo->data->stop_mutex);
			if (++philo->data->max_ate == philo->data->philo_amount)
			{
				pthread_mutex_unlock(&philo->data->stop_mutex);
				is_dead(philo, 2);
			}
			pthread_mutex_unlock(&philo->data->stop_mutex);
			return (NULL);
		}
	}
	return (NULL);
}
