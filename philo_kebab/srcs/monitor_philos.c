/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_philos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismirand <ismirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 14:37:13 by malves-b          #+#    #+#             */
/*   Updated: 2024/10/22 13:46:59 by ismirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	check_dead(t_exe *exe)
{
	int	i;

	i = 0;
	while (i < exe->p_amount)
	{
		if ((int)(get_current_time() - exe->philos[i].last_meal_time) >
			exe->time_to_die)
		{
			pthread_mutex_lock(&exe->write_lock);
			printf("\033[31m%lu", get_current_time() - exe->start_time);
			printf(" %i died\n\033[0m", exe->philos[i].id);
			pthread_mutex_unlock(&exe->write_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

void	*monitor_aux(void *arg)
{
	t_exe	*exe;
	int		i;

	exe = (t_exe *)arg;
	while (1)
	{
		i = -1;
		pthread_mutex_lock(&exe->dead_lock);
		if (check_dead(exe))
			exe->dead_flag = 1;
		if (exe->target_eat > 0)
		{
			while (++i < exe->p_amount)
			{
				if (exe->philos[i].eated_amount < exe->target_eat)
					break ;
			}
			if (i == exe->p_amount)
				exe->all_eaten_flag = 1;
		}
		pthread_mutex_unlock(&exe->dead_lock);
		if (exe->dead_flag || exe->all_eaten_flag)
			return ((void *)1);
		ft_usleep(2, exe->philos);
	}
}

int	monitor_philos(t_exe *pgr)
{
	pthread_t	monitor_eat;
	void		*ret;

	if (pthread_create(&monitor_eat, NULL, monitor_aux, pgr))
	{
		puts ("\033[31mPthread create! *monitor_aux*\033[0m");
		return (-1);
	}
	pthread_join(monitor_eat, (void **) &ret);
	if (ret == (void *)1)
	{
		return (1);
	}
	return (0);
}

void	clean_program(t_exe *pgr)
{
	int	i;

	i = -1;
	while (++i < pgr->p_amount)
	{
		if (pthread_join(pgr->philos[i].thread, NULL) != 0)
		{
			puts("\033[31mFailed to join thread\n\033[0m");
			return ;
		}
	}
	i = -1;
	while (++i < pgr->p_amount)
	{
		if (pthread_mutex_destroy(&pgr->forks[i]) != 0)
			return ;
	}
	if (pthread_mutex_destroy(&pgr->write_lock) != 0)
		return ;
	if (pthread_mutex_destroy(&pgr->dead_lock) != 0)
		return ;
	free(pgr->philos);
	free(pgr->forks);
	free(pgr);
}
