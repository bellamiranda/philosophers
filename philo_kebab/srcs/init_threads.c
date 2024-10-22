/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malves-b <malves-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:34:55 by malves-b          #+#    #+#             */
/*   Updated: 2024/10/09 15:48:20 by malves-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	initialize_philosophers(t_exe *pgr)
{
	int	i;

	i = -1;
	while (++i < pgr->p_amount)
	{
		pgr->philos[i].id = i + 1;
		pgr->philos[i].eated_amount = 0;
		pgr->philos[i].exe = pgr;
		pgr->philos[i].left_fork = &pgr->forks[i];
		pgr->philos[i].last_meal_time = get_current_time();
		if (pthread_create(&pgr->philos[i].thread, NULL, &define_action,
				&pgr->philos[i]) != 0)
		{
			puts("\033[31mError creating thread\033[0m");
			pthread_mutex_lock(&pgr->dead_lock);
			pgr->dead_flag = 1;
			pthread_mutex_unlock(&pgr->dead_lock);
			return (-1);
		}
	}
	return (0);
}

int	initialize_mutexes(t_exe *pgr)
{
	int	i;

	i = -1;
	while (++i < pgr->p_amount)
	{
		if (pthread_mutex_init(&pgr->forks[i], NULL) != 0)
		{
			puts("\033[31mError creating mutex\033[0m");
			return (-1);
		}
	}
	if (pthread_mutex_init(&pgr->write_lock, NULL) != 0)
	{
		puts("\033[31mError creating mutex\033[0m");
		return (-1);
	}
	if (pthread_mutex_init(&pgr->dead_lock, NULL) != 0)
	{
		puts("\033[31mError creating mutex\033[0m");
		return (-1);
	}
	return (0);
}

int	init_threads(t_exe *pgr, char **args)
{
	pgr->p_amount = ft_atoi(args[1]);
	pgr->time_to_die = ft_atoi(args[2]);
	pgr->time_to_eat = ft_atoi(args[3]);
	pgr->time_to_sleep = ft_atoi(args[4]);
	pgr->dead_flag = 0;
	pgr->all_eaten_flag = 0;
	pgr->start_time = get_current_time();
	pgr->philos = malloc(sizeof(t_philo) * pgr->p_amount);
	if (!pgr->philos)
	{
		puts("\033[31mError allocating memory *philos*\033[0m");
		return (-1);
	}
	ft_memset(pgr->philos, 0, sizeof(t_philo) * pgr->p_amount);
	pgr->forks = malloc(sizeof(pthread_mutex_t) * pgr->p_amount);
	if (!pgr->philos || !pgr->forks)
	{
		puts("\033[31mError allocating memory *init_threads*\033[0m");
		return (-1);
	}
	if (initialize_mutexes(pgr) != 0)
		return (-1);
	if (initialize_philosophers(pgr) != 0)
		return (-1);
	return (0);
}
