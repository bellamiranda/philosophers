/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismirand <ismirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 14:46:47 by ismirand          #+#    #+#             */
/*   Updated: 2024/10/22 15:32:11 by ismirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*routine(void *x)
{
	t_philo	*philo;

	philo = (t_philo *)x;
	if (threads_fail(philo->table))
		return (NULL);
	//printf("%i\n", philo->table->table_ready);//acho que ta com problema aqui
	//if (philo->id % 2 == 0)
	//	ft_usleep(10);//os pares esperam, assim os impares pegam o garfo primeiro
	while (42)
	{
		if (dead_or_full(philo->table))//caso algum morra ou todos terminem de comer
			return (NULL);
		if (philo->id % 2 != 0)//impares comecam pegando o garfo da esqueda
			eating(philo, philo->l_fork, philo->r_fork);
		else// if (philo->id % 2 == 0)
			eating(philo, philo->r_fork, philo->l_fork);
		sleeping(philo);
		thinking(philo);
	}
	//return (NULL);
}

void	eating(t_philo *ph, pthread_mutex_t *a_fork, pthread_mutex_t *b_fork)
{
	if (dead_or_full(ph->table))
		return ;
	pthread_mutex_lock(a_fork);
	print(ph, TAKE_FORK, WHITE);
	pthread_mutex_lock(b_fork);
	print(ph, TAKE_FORK, WHITE);
	print(ph, EAT, GREEN);
	pthread_mutex_lock(&ph->table->monitor);
	ph->last_meal = get_current_time() - ph->table->start;
	pthread_mutex_unlock(&ph->table->monitor);
	ft_usleep(ph->table->t_eat);
	pthread_mutex_unlock(a_fork);
	pthread_mutex_unlock(b_fork);
	pthread_mutex_lock(&ph->table->monitor);
	ph->meals++;
	if (ph->meals == ph->table->meals)
		ph->is_full = true;
	pthread_mutex_unlock(&ph->table->monitor);
}

void	sleeping(t_philo *philo)
{
	if (dead_or_full(philo->table))//isso nao ta funcionando
		return ;
	print(philo, SLEEP, CYAN);
	ft_usleep(philo->table->t_sleep);
/* 	pthread_mutex_lock(&philo->table->monitor);
	philo->table->is_dead = true;
	pthread_mutex_unlock(&philo->table->monitor); */
}

//so pra aguardar os outros terminarem de comer
void	thinking(t_philo *philo)
{
	if (dead_or_full(philo->table))
		return ;
	print(philo, THINK, MGT);
	if (philo->table->n_philos % 2 != 0)
		ft_usleep(1);
}
