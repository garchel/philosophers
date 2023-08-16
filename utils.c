/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauvicto <pauvicto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 18:51:13 by pauvicto          #+#    #+#             */
/*   Updated: 2023/08/16 20:56:55 by pauvicto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	ft_get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	is_dead(t_philo *philo, int nb)
{
	pthread_mutex_lock(&(philo->data->dead_mutex));
	if (nb)
		philo->data->stop_condition = true;
	if (philo->data->stop_condition)
	{
		pthread_mutex_unlock(&(philo->data->dead_mutex));
		return (true);
	}
	pthread_mutex_unlock(&(philo->data->dead_mutex));
	return (false);
}

void	ft_usleep(int ms)
{
	long int	time;

	time = ft_get_time();
	while (ft_get_time() - time < ms)
		usleep(ms / 10);
}

void	philo_print(t_philo *philo, char *str)
{
	unsigned long	time;

	pthread_mutex_lock(&(philo->data->write_mutex));
	time = ft_get_time() - philo->data->start_time;
	if (!philo->data->stop_condition && time >= 0 \
			&& time <= INT_MAX && !is_dead(philo, 0))
		printf("%lu %d %s", time, philo->pos, str);
	pthread_mutex_unlock(&(philo->data->write_mutex));
}

int	ft_atoi(const char *str)
{
	int	i;
	int	res;
	int	signe;

	i = 0;
	signe = 1;
	res = 0;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == ' '))
		i++;
	if (str[i] == '-')
	{
		signe *= -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * signe);
}
