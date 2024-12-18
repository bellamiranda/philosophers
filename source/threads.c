/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismirand <ismirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:27:34 by ismirand          #+#    #+#             */
/*   Updated: 2024/10/29 13:37:33 by ismirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	threads(t_table *table, int i)
{
	void	*ret;

	while (++i < table->n_philos)
	{
		if (pthread_create(&table->philos[i].thread, NULL, &routine,
				&table->philos[i]) != 0)
		{
			table->fail_thread_creation = true;
			return (print_error(6));
		}
	}
	if (pthread_create(&table->thread_monitor, NULL, &monitoring, table) != 0)
	{
		table->fail_thread_creation = true;
		return (print_error(6));
	}
	pthread_mutex_lock(&table->monitor);
	table->start = get_current_time();
	table->table_ready = true;
	pthread_mutex_unlock(&table->monitor);
	if (pthread_join(table->thread_monitor, (void **)&ret) != 0)
		return (print_error(7));
	if (ret == (void *)1)
		return (join_and_clean(table));
	return (EXIT_SUCCESS);
}

int	join_and_clean(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->n_philos)
	{
		if (pthread_join(table->philos[i].thread, NULL) != 0)
			return (print_error(7));
		pthread_mutex_destroy(&table->forks[i]);
	}
	pthread_mutex_destroy(&table->monitor);
	pthread_mutex_destroy(&table->print);
	pthread_mutex_destroy(&table->end);
	pthread_mutex_destroy(&table->check);
	free(table->forks);
	free(table->philos);
	return (EXIT_SUCCESS);
}

int	threads_fail(t_table *table)
{
	while (42)
	{
		pthread_mutex_lock(&table->monitor);
		if (table->fail_thread_creation)
		{
			pthread_mutex_unlock(&table->monitor);
			return (EXIT_FAILURE);
		}
		if (table->table_ready)
		{
			pthread_mutex_unlock(&table->monitor);
			break ;
		}
		pthread_mutex_unlock(&table->monitor);
	}
	return (EXIT_SUCCESS);
}

int	one_philo(char *t_die)
{
	printf(BLUE"0 1 has taken a fork\n"RESET);
	ft_usleep(ft_atoi(t_die));
	printf(RED"%s 1 died\n"RESET, t_die);
	return (EXIT_FAILURE);
}
