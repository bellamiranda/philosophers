/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismirand <ismirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 14:46:47 by ismirand          #+#    #+#             */
/*   Updated: 2024/10/11 15:29:47 by ismirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*routine(void *x)
{
	t_philo	*philo;

	philo = (t_philo *)x;
	if (threads_fail(philo->table))
		return (NULL);//pq retorna NULL?
	if (philo->table->n_philos == 1)
		return (one_philo(philo));
}

/* void	*routine(void *philo)
{
	t_philo		*ph;

	ph = (t_philo *)philo;
	if (!wait_threads_creation(ph->prog))
		return (NULL);
	if (ph->id % 2 == 0)
		ft_usleep(10);
	if (ph->prog->n_philos == 1)
		return (one_philo(ph));
	while (1)
	{
		if (check_dinner_end(ph) == 1)
			return (NULL);
		if (ph->id % 2 != 0)
			eating(ph, ph->l_fork, ph->r_fork);
		else if (ph->id % 2 == 0)
			eating(ph, ph->r_fork, ph->l_fork);
		sleeping(ph);
		thinking(ph);
	}
	return (NULL);
} */

void	*one_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	print(philo, TAKE_FORK, CYAN);
	pthread_mutex_unlock(philo->l_fork);
	return (NULL);
}
