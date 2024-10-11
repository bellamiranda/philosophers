/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismirand <ismirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 13:38:01 by ismirand          #+#    #+#             */
/*   Updated: 2024/10/11 15:40:12 by ismirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/*
@return Current time in milisseconds
	gettimeofday - stores in timeval struct the current time
	t.tv_sec - stores the time in seconds (*1000 to convert do milissec)
	t.tv_usec - stores the microsseconds part (/1000 to milissec)
*/
size_t	get_current_time(void)
{
	struct timeval	t;
	size_t			current;

	gettimeofday(&t, NULL);
	current = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	return (current);
}

/* 
Uses get_current_time to be precise on the usleep
 */
void	ft_usleep(size_t time)
{
	size_t	start;

	start = get_current_time();
	while (get_current_time() - start < time)
		usleep(500);
}

int	print(t_philo *philo, char *str, char *c)
{
	pthread_mutex_lock(&philo->table->wait);
	if (!philo->table->is_dead && !philo->table->full)//?
	{
		pthread_mutex_lock(&philo->table->print);
		printf("%s%zu %i %s\n"RESET, c, get_current_time()
			- philo->table->start, philo->id, str);
		pthread_mutex_unlock(&philo->table->print);
	}
	pthread_mutex_unlock(&philo->table->wait);
}
