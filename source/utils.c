/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismirand <ismirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 13:38:01 by ismirand          #+#    #+#             */
/*   Updated: 2024/10/22 13:09:43 by ismirand         ###   ########.fr       */
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
	pthread_mutex_lock(&philo->table->print);
	if (!philo->table->is_dead && !philo->table->full)
	{
		printf("%s%zu %i %s\n"RESET, c, get_current_time()
			- philo->table->start, philo->id, str);
	}
	pthread_mutex_unlock(&philo->table->print);
	return (0);
}

int	print_error(int flag)
{
	if (flag == 0)
		printf(RED"Error: fork's malloc\n"RESET);
	if (flag == 1)
		printf(RED"Error: init_mutex\n"RESET);
	if (flag == 2)
		printf(RED"Error: mutex_destroy\n"RESET);
	if (flag == 3)
		printf(RED"Error: philo's malloc\n"RESET);
	if (flag == 4)
		printf(RED"Error: init_philos\n"RESET);
	if (flag == 5)
		printf(RED"Error: init_table\n"RESET);
	if (flag == 6)
		printf(RED"Error: thread creation\n"RESET);
	if (flag == 7)
		printf(RED"Error: thread join\n"RESET);
	return (EXIT_FAILURE);
}
