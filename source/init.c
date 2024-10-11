/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismirand <ismirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 18:33:04 by ismirand          #+#    #+#             */
/*   Updated: 2024/10/11 15:35:37 by ismirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	init_table(char*argv[], t_table *table)
{
	table->n_philos = ft_atoi(argv[1]);
	table->t_die = ft_atoi(argv[2]);
	table->t_eat = ft_atoi(argv[3]);
	table->t_sleep = ft_atoi(argv[4]);
	table->meals = 0;
	if (argv[5])
		table->meals = ft_atoi(argv[5]);
	table->is_dead = false;
	table->full = false;
	table->threads_ready = false;
	table->fail_thread_creation = false;
	if (init_mutex(table))
		return (EXIT_FAILURE);
	if (init_philos(table))
		return (EXIT_FAILURE);
	return(EXIT_SUCCESS);
}

int	init_mutex(t_table *table)
{
	pthread_mutex_t	*forks;
	int				i;

	i = -1;
	forks = malloc(sizeof(pthread_mutex_t) * table->n_philos);//cria a array do total de garfos na mesa
	if (!forks)
		return (EXIT_FAILURE);
	table->forks = forks;
	while (++i < table->n_philos)
		if (pthread_mutex_init(&forks[i], NULL) != 0)//inicializa a mutex dos garfos de cada philo
			return (destroy_mutex(table, (i + 1), 0));
	if (pthread_mutex_init(&table->wait, NULL) != 0)
		return (destroy_mutex(table, i, 1));
	if (pthread_mutex_init(&table->print, NULL) != 0)
		return (destroy_mutex(table, i, 2));
	if (pthread_mutex_init(&table->monitor, NULL) != 0)
		return (destroy_mutex(table, i, 3));
	return (EXIT_SUCCESS);//escrever msg de erro
}

int	destroy_mutex(t_table *table, int i, int flag)
{
	while (--i >= 0)
		pthread_mutex_destroy(&table->forks[i]);
	if (flag)
		pthread_mutex_destroy(&table->wait);
	else if (flag == 2 || flag == 3)
		pthread_mutex_destroy(&table->print);
	else if (flag == 3)
		pthread_mutex_destroy(&table->monitor);
	return (EXIT_FAILURE);
}

int	init_philos(t_table *table)
{
	t_philo	*philo;
	int		i;

	i = -1;
	philo = malloc(sizeof(t_philo) * table->n_philos);
	if (!philo)
		return (EXIT_FAILURE);
	table->philos = philo;
	while (++i < table->n_philos)
	{
		philo[i].id = i + 1;
		philo[i].meals = 0;
		philo[i].is_full = false;
		philo[i].last_meal = 0;
		philo[i].table = table;
		philo[i].l_fork = &table->forks[i];
		if (i == table->n_philos - 1)//aponta o garfo da direita do ultimo para o garfo do primeiro
			philo[i].r_fork = &table->forks[0];
		else
			philo[i].r_fork = &table->forks[i + 1];
	}
	return (EXIT_SUCCESS);
}
