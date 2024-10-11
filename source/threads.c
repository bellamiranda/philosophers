/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismirand <ismirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:27:34 by ismirand          #+#    #+#             */
/*   Updated: 2024/10/11 15:50:19 by ismirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	threads(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->n_philos)
	{
		if (pthread_create(&table->philos[i].thread, NULL, &routine,
				&table->philos[i]) != 0)
		{
			table->fail_thread_creation = true;//checar se precisa ou se e so retornar erro
			return (EXIT_FAILURE);//escrever msg de erro
		}
	}
	if (pthread_create(&table->thread_monitor, NULL, &monitoring, &table) != 0)
	{
		table->fail_thread_creation = true;
		return (EXIT_FAILURE);//escrever msg de erro
	}
	table->start = get_current_time();
	pthread_mutex_lock(&table->monitor);
	table->threads_ready = true;
	pthread_mutex_unlock(&table->monitor);
	i = -1;
	while (++i < table->n_philos)
		if (pthread_join(table->philos[i].thread, NULL) != 0)
			return (EXIT_FAILURE);//escrever msg de erro
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
		if (!table->threads_ready)
		{
			pthread_mutex_unlock(&table->monitor);
			break ;
		}
		pthread_mutex_unlock(&table->monitor);
	}
	return (EXIT_SUCCESS);
}
