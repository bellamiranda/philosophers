/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malves-b <malves-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 13:35:44 by malves-b          #+#    #+#             */
/*   Updated: 2024/10/10 15:19:26 by malves-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>

# define EAT 1
# define SLEEP 2
# define THINK 3

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eated_amount;
	size_t			last_meal_time;
	pthread_mutex_t	*left_fork;
	struct s_exe	*exe;
}	t_philo;

typedef struct s_exe
{
	int				p_amount;
	int				target_eat;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				dead_flag;
	int				all_eaten_flag;
	size_t			start_time;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	dead_lock;
}	t_exe;

/* ---------------------------------- UTILS --------------------------------- */
int		ft_atoi(char *nptr);
int		ft_isdigit(int i);
int		check_arg(char **argv, int argc, int j);
int		ft_usleep(size_t milliseconds, t_philo *philo);
size_t	get_current_time(void);
void	print_msg(char *str, t_philo *philo, int id, int action);
int		dead_loop(t_philo *philo);
void	*ft_memset(void *b, int c, size_t len);
/* -------------------------------------------------------------------------- */

/* --------------------------------- ACTIONS -------------------------------- */
void	ft_sleep(t_philo *philo);
void	think(t_philo *philo);
void	eat(t_philo *philo);
void	*define_action(void *arg);
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
int		init_threads(t_exe *pgr, char **args);
void	clean_program(t_exe *pgr);
int		monitor_philos(t_exe *pgr);
int		ft_aux(int argc, char **argv);
int		is_dead(t_philo *philo);
/* -------------------------------------------------------------------------- */

/* 
Starvation :
Race conditions :
Data race :
*/

#endif
