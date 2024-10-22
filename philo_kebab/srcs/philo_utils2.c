/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malves-b <malves-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 10:01:21 by malves-b          #+#    #+#             */
/*   Updated: 2024/10/10 15:22:02 by malves-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	dead_loop(t_philo *philo)
{
	if (!philo->exe)
	{
		return (1);
	}
	pthread_mutex_lock(&philo->exe->dead_lock);
	if (philo->exe->dead_flag || philo->exe->all_eaten_flag)
	{
		pthread_mutex_unlock(&philo->exe->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->exe->dead_lock);
	return (0);
}

void	print_msg(char *str, t_philo *philo, int id, int action)
{
	size_t	timestamp;

	pthread_mutex_lock(&philo->exe->dead_lock);
	pthread_mutex_lock(&philo->exe->write_lock);
	if (!philo->exe->dead_flag && !philo->exe->all_eaten_flag)
	{
		timestamp = get_current_time() - philo->exe->start_time;
		printf("%zu ", timestamp);
		if (action == EAT)
		{
			printf("\033[32m");
			printf(str, id);
			printf("\033[0m");
		}
		else if (action == SLEEP)
		{
			printf("\033[33m");
			printf(str, id);
			printf("\033[0m");
		}
		else
			printf(str, id);
	}
	pthread_mutex_unlock(&philo->exe->write_lock);
	pthread_mutex_unlock(&philo->exe->dead_lock);
}

int	is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->exe->dead_lock);
	if (philo->exe->dead_flag || philo->exe->all_eaten_flag)
	{
		pthread_mutex_unlock(&philo->exe->dead_lock);
		return (0);
	}
	else
	{
		pthread_mutex_unlock(&philo->exe->dead_lock);
		return (1);
	}
}
