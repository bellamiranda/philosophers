/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malves-b <malves-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 17:30:13 by malves-b          #+#    #+#             */
/*   Updated: 2024/10/10 15:16:06 by malves-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_sleep(t_philo *philo)
{
	if (dead_loop(philo))
		return ;
	print_msg("%i is sleeping\n", philo, philo->id, SLEEP);
	ft_usleep(philo->exe->time_to_sleep, philo);
}

void	think(t_philo *philo)
{
	if (dead_loop(philo))
		return ;
	print_msg("%i is thinking\n", philo, philo->id, THINK);
}

int	get_fork(t_philo *philo)
{
	int	right_fork_id;

	right_fork_id = (philo->id) % philo->exe->p_amount;
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print_msg("%i has taken a fork\n", philo, philo->id, 0);
		pthread_mutex_lock(&philo->exe->forks[right_fork_id]);
		print_msg("%i has taken a fork\n", philo, philo->id, 0);
	}
	else
	{
		pthread_mutex_lock(&philo->exe->forks[right_fork_id]);
		print_msg("%i has taken a fork\n", philo, philo->id, 0);
		pthread_mutex_lock(philo->left_fork);
		print_msg("%i has taken a fork\n", philo, philo->id, 0);
	}
	return (right_fork_id);
}

void	eat(t_philo *philo)
{
	int	right_fork_id;

	right_fork_id = get_fork(philo);
	if (dead_loop(philo))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(&philo->exe->forks[right_fork_id]);
		return ;
	}
	print_msg ("%i is eating\n", philo, philo->id, EAT);
	ft_usleep(philo->exe->time_to_eat, philo);
	pthread_mutex_lock(&philo->exe->dead_lock);
	philo->last_meal_time = get_current_time();
	if (philo->eated_amount != -5)
		++philo->eated_amount;
	pthread_mutex_unlock(&philo->exe->dead_lock);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(&philo->exe->forks[right_fork_id]);
}

void	*define_action(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (dead_loop(philo))
			return (NULL);
		eat(philo);
		if (dead_loop(philo))
			return (NULL);
		ft_sleep(philo);
		if (dead_loop(philo))
			return (NULL);
		think(philo);
	}
	return (NULL);
}
