/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauvicto <pauvicto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 18:51:26 by pauvicto          #+#    #+#             */
/*   Updated: 2023/08/15 01:47:34 by pauvicto         ###   ########.fr       */
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

# define INVALID_PARAMETER_AMOUNT 1
# define INVALID_PARAMETER_TYPE 2
# define PHILO_MALLOC_ERROR 3
# define INIT_DATA_ERROR 4
# define INIT_MUTEX_ERROR 5
# define INIT_PHILOS_ERROR 6

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
	//phtread_mutex_t	*forks_mutex;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t stop_mutex;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	dead_mutex;
	int				error;
}				t_data;

//error_handler.c
void free_handler(t_data *data);
int error_handler(t_data *data);

//free_handler.c

//init_handler.c
int init_handler (t_data *data, int argc, char* argv[]);

//main.c

//philo_handler.c
void	*routine(void *philosofer);
void	philo_eat(t_philo *philo);
void	philo_forks(t_philo *philo);
void	*philo_verify_death(void *phi);

// utils
long long	timestamp(void);
int	is_dead(t_philo *philo, int nb);
void	ft_usleep(int ms);
void	print(t_philo *philo, char *str);
bool	is_all_digits(char **argv);
int	ft_atoi(const char *str);

//philo_handler_test.c
void test_philo_verify_death();
void test_philo_forks();
void test_philo_eat();
void test_routine();
#endif
