/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismirand <ismirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 15:03:56 by ismirand          #+#    #+#             */
/*   Updated: 2024/10/29 13:18:06 by ismirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*monitoring(void *x)
{
	t_table	*table;
	int		i;

	table = (t_table *)x;
	while (42)
	{
		i = 0;
		while (i < table->n_philos)
		{
			pthread_mutex_lock(&table->monitor);
			if (is_dead(table, i) || is_all_full(table))
			{
				pthread_mutex_unlock(&table->monitor);
				return ((void *)1);
			}
			pthread_mutex_unlock(&table->monitor);
			i++;
		}
	}
	return (NULL);
}

int	is_dead(t_table *table, int i)
{
	pthread_mutex_lock(&table->end);
	if ((get_current_time() - table->start - table->philos[i].last_meal
			>= (size_t)table->t_die) && !table->philos[i].is_full)
	{
		print(&table->philos[i], DIED, RED);
		pthread_mutex_lock(&table->check);
		table->is_dead = true;
		pthread_mutex_unlock(&table->check);
		pthread_mutex_unlock(&table->end);
		return (true);
	}
	pthread_mutex_unlock(&table->end);
	return (false);
}

int	is_all_full(t_table *table)
{
	int	i;

	i = 0;
	while (++i <= table->n_philos)
	{
		pthread_mutex_lock(&table->end);
		if (!table->philos[i].is_full)
		{
			pthread_mutex_unlock(&table->end);
			return (false);
		}
		pthread_mutex_unlock(&table->end);
	}
	pthread_mutex_lock(&table->end);
	table->full = true;
	pthread_mutex_unlock(&table->end);
	return (true);
}

int	dead_or_full(t_table *table)
{
	pthread_mutex_lock(&table->check);
	if (table->is_dead || table->full)
	{
		pthread_mutex_unlock(&table->check);
		return (true);
	}
	pthread_mutex_unlock(&table->check);
	return (false);
}
