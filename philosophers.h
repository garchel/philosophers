/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauvicto <pauvicto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 18:51:26 by pauvicto          #+#    #+#             */
/*   Updated: 2023/08/16 22:09:44 by pauvicto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

// Prompt colors
# define GRN	"\001\e[0;32m\002"
# define MAG	"\001\e[0;35m\002"
# define WHT	"\001\e[0;37m\002"
# define CRESET	"\001\e[0m\002"

# define TRUE 1
# define FALSE 0
# define SUCCESS 1
# define FAILED 0

# define INVALID_PARAMETER_QUANT 1
# define INVALID_PARAMETER_TYPE 2
# define INVALID_PARAMETER_FORMAT 3
# define PHILO_MALLOC_ERROR 4
# define INIT_DATA_ERROR 5
# define INIT_MUTEX_ERROR 6
# define INIT_PHILOS_ERROR 7

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdbool.h>
# include <limits.h>

typedef struct s_philo
{
	struct s_data	*data;
	int				ate_times;
	long int		last_ate;
	int				pos;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	*right_fork;
	pthread_t		thread_id;
	pthread_t		death_monitor_thread;
}				t_philo;

typedef struct s_data
{
	unsigned long	start_time;
	int				stop_condition;
	int				max_ate;
	int				philo_amount;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_count_max;
	struct s_philo	*philo;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	dead_mutex;
	int				error;
}				t_data;

//error_handler.c
void		free_handler(t_data *data);
int			error_handler(t_data *data);

//init_handler.c
int			init_handler(t_data *data, int argc, char *argv[]);

//init_utils.c
void		forks_handler(t_data *data);
void		*philo_death_monitor(void *philosofer);
int			threads_maker(t_data *data);

//philo_handler.c
void		*routine(void *philosofer);
void		philo_eat(t_philo *philo);
void		philo_forks(t_philo *philo);
void		*philo_verify_death(void *phi);

// utils
long long	ft_get_time(void);
int			is_dead(t_philo *philo, int nb);
void		ft_usleep(int ms);
void		philo_print(t_philo *philo, char *str);
bool		validate_digits(char **argv);
int			ft_atoi(const char *str);

#endif
