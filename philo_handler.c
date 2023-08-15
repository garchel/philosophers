/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauvicto <pauvicto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 18:51:33 by pauvicto          #+#    #+#             */
/*   Updated: 2023/08/15 22:41:39 by pauvicto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philosophers.h"

void	*philo_verify_death(void *phi)
{
	t_philo	*philo;

	
	philo = (t_philo *)phi; // Converte o ponteiro genérico para o tipo t_philo
	ft_usleep(philo->data->time_to_die + 1); // Aguarda o tempo de vida do filósofo + 1 antes de verificar se ele morreu
	pthread_mutex_lock(&philo->data->meal_mutex); // Bloqueia os mutexes de refeição e escrita
	pthread_mutex_lock(&philo->data->stop_mutex);
	if (!is_dead(philo, 0) && (timestamp() - philo->last_ate) >= (long)(philo->data->time_to_die)) // Verifica se o filósofo não está morto e se o tempo desde a última refeição é maior ou igual ao tempo de vida
	{
		pthread_mutex_unlock(&philo->data->meal_mutex); // Desbloqueia os mutexes de refeição e escrita
		pthread_mutex_unlock(&philo->data->stop_mutex);
		print(philo, " died\n"); // Imprime que o filósofo morreu
		is_dead(philo, 1); // Marca o filósofo como morto
	}
	pthread_mutex_unlock(&philo->data->meal_mutex); // Desbloqueia os mutexes de refeição e escrita
	pthread_mutex_unlock(&philo->data->stop_mutex);
	return (NULL);
}

// Função que faz o filósofo pegar os garfos
void	philo_forks(t_philo *philo)
{
	pthread_mutex_lock(&(philo->left_fork)); // Bloqueia o mutex do garfo esquerdo
	print(philo, " has taken a fork\n"); // Imprime que o filósofo pegou um garfo
	if (philo->data->philo_amount == 1) // Se houver apenas um filósofo, aguarda o tempo de vida * 2 e retorna
	{
		ft_usleep(philo->data->time_to_die * 2);
		return ;
	}
	pthread_mutex_lock(philo->right_fork); // Bloqueia o mutex do garfo direito
	print(philo, " has taken a fork\n"); // Imprime que o filósofo pegou outro garfo
}

// Função que faz o filósofo comer
void	philo_eat(t_philo *philo)
{
	
	print(philo, " is eating\n"); // Imprime que o filósofo está comendo
	pthread_mutex_lock(&(philo->data->meal_mutex)); // Bloqueia o mutex de refeição
	philo->last_ate = timestamp(); // Atualiza o tempo da última refeição e a quantidade de vezes que o filósofo comeu
	philo->ate_times++;
	pthread_mutex_unlock(&(philo->data->meal_mutex)); // Desbloqueia o mutex de refeição
	ft_usleep(philo->data->time_to_eat); // Aguarda o tempo de refeição
	pthread_mutex_unlock(philo->right_fork); // Desbloqueia os mutexes dos garfos
	pthread_mutex_unlock(&philo->left_fork);
	print(philo, " is sleeping\n"); // Imprime que o filósofo está dormindo
	ft_usleep(philo->data->time_to_sleep); // Aguarda o tempo de sono
	print(philo, " is thinking\n"); // Imprime que o filósofo está pensando
}

// Função que representa o comportamento do filósofo
void	*routine(void *philosofer)
{
	t_philo		*philo;
	pthread_t	death_monitor;

	philo = (t_philo *)philosofer; // Converte o ponteiro genérico para o tipo t_philo
	if (philo->data->philo_amount % 2 == 0) // Se a quantidade de filósofos for par, aguarda um tempo para evitar deadlocks
		ft_usleep(philo->data->time_to_eat / 10);
	while (!is_dead(philo, 0)) // Enquanto não houver filósofo morto
	{
		
		pthread_create(&death_monitor, NULL, philo_verify_death, philosofer); // Cria a thread que vai monitorar se o filósofo morreu		
		philo_forks(philo); // Faz o filósofo pegar os garfos
		philo_eat(philo); // Faz o filósofo comer
		pthread_detach(death_monitor); // Desanexa a thread de monitoramento de morte
		if (philo->ate_times == philo->data->eat_count_max && philo->data->eat_count_max != 0) // Se o filósofo comeu a quantidade máxima de vezes permitida
		{
			pthread_mutex_lock(&philo->data->stop_mutex); // Bloqueia o mutex de escrita
			if (++philo->data->max_ate == philo->data->philo_amount) // Incrementa a quantidade de filósofos que comeram a quantidade máxima de vezes permitida
			{
				pthread_mutex_unlock(&philo->data->stop_mutex); // Desbloqueia o mutex de escrita e marca o filósofo como morto
				is_dead(philo, 2);
			}
			pthread_mutex_unlock(&philo->data->stop_mutex); // Desbloqueia o mutex de escrita
			return (NULL);
		}
	}
	return (NULL);
}
