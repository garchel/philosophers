/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauvicto <pauvicto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 18:51:44 by pauvicto          #+#    #+#             */
/*   Updated: 2023/08/15 20:58:23 by pauvicto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int init_data(t_data *data, int argc, char* argv[])
{
	if (!(data->philo = malloc(sizeof(t_philo) * data->philo_amount)))
		return (data->error = PHILO_MALLOC_ERROR);
	data->start_time = 0;
	data->stop_condition = 0;
	data->max_ate = 0;
	data->philo_amount = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->eat_count_max = ft_atoi(argv[5]);
	else
		data->eat_count_max = 0;
	if (data->philo_amount < 1 || data->time_to_die < 0 || data->time_to_eat < 0
		|| data->time_to_sleep < 0 || data->eat_count_max < 0)
		return (data->error = INIT_DATA_ERROR);
	return (0);
}

int init_mutexes(t_data *data)
{
	if (pthread_mutex_init(&data->write_mutex, NULL) != 0)
		return (data->error = INIT_MUTEX_ERROR);
	if (pthread_mutex_init(&data->meal_mutex, NULL) != 0)
		return (data->error = INIT_MUTEX_ERROR);
	if (pthread_mutex_init(&data->dead_mutex, NULL) != 0)
		return (data->error = INIT_MUTEX_ERROR);
	return (0);
}

int	init_philos(t_data *data)
{
	int	i;

	data->start_time = timestamp(); // Armaneza o tempo de início
	i = -1;
	while (++i < data->philo_amount)
	{
		data->philo[i].data = data; // Atribui o ponteiro para a estrutura de dados
		data->philo[i].ate_times = 0; // Atribui a quantidade de refeições
		data->philo[i].last_ate = 0; // Atribui o tempo da última refeição
		data->philo[i].pos = i + 1; // Atribui o número do filósofo
		pthread_mutex_init(&(data->philo[i].left_fork), NULL); // Inicializa o mutex do garfo esquerdo
		//pthread_mutex_init(data->philo[i].right_fork, NULL); // Inicializa o mutex do garfo direito
		if (i == data->philo_amount - 1) // Se for o último filósofo, o garfo direito é o primeiro (Fechando o círculo)
			data->philo[i].right_fork = &data->philo[0].left_fork;
		else // Se não, o garfo do próximo filósofo é o garfo direito do filósofo atual
			data->philo[i].right_fork = &data->philo[i + 1].left_fork; 
		if (pthread_create(&data->philo[i].thread_id, NULL, \
				&routine, &(data->philo[i])) != 0) // Cria a thread do filósofo com a função routine
			return (data->error = INIT_PHILOS_ERROR);
	}
	i = -1;
	while (++i < data->philo_amount)
		if (pthread_join(data->philo[i].thread_id, NULL) != 0) // Aguarda o término da execução das threads para evitar que o programa termine antes da hora ocasionando em um erro de execução
			return (data->error = INIT_PHILOS_ERROR);
	return (0);
}

int init_handler (t_data *data, int argc, char* argv[])
{
	printf("Init data \n");
	if (init_data(data, argc, argv) != 0)
		return (error_handler(data));
	printf("Init Mutexes \n");
	if (init_mutexes(data) != 0)
		return (error_handler(data));
	printf("Init Philos \n");
	if (init_philos(data) != 0)
		return (error_handler(data));
	printf("Init Philos FIM \n");
	return (0);
}



// A função init_philos retornaria antes das threads de filósofos terem a chance de terminar suas execuções.

// As threads de filósofos continuariam a ser executadas após o término da função init_philos, já que não haveria espera explícita por meio de pthread_join.

// Isso poderia levar a uma execução desordenada e imprevisível, onde threads ainda ativas tentariam acessar e modificar os mesmos recursos compartilhados que a função init_philos poderia estar tentando limpar ou liberar.

// Poderia haver problemas de acesso concorrente não controlado, resultando em resultados inconsistentes ou até mesmo falhas do programa.