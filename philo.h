/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismirand <ismirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:56:23 by ismirand          #+#    #+#             */
/*   Updated: 2024/10/29 13:16:01 by ismirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h> //gettimeofday
# include <pthread.h> //pthread_t, pthread_mutex_t
# include <stdint.h> //uint64_t
# include <stdbool.h>
# include <limits.h> //INT_MAX

# define RESET	"\033[0m"
# define RED	"\033[31;1m"
# define GREEN	"\033[32;1m"
# define CYAN	"\033[36;1m"
# define WHITE	"\033[37;1m"
# define YELLOW	"\033[33;1m"
# define BLUE	"\033[34;1m"
# define MGT	"\033[35;1m"
# define ORANGE "\033[1;38;5;208m"

# define TAKE_FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIED "died"

/* typedef enum	e_state
{
	EATING,
	SLEEPING,
	THINKING,
	DEAD,
	FULL
}	t_state; */

typedef struct s_philo
{
	int					id;
	int					meals;
	bool				is_full;
	size_t				last_meal;
	struct s_table		*table;
	pthread_t			thread;
	pthread_mutex_t		*l_fork;
	pthread_mutex_t		*r_fork;
}					t_philo;

typedef struct s_table
{
	int				n_philos;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				meals;
	size_t			start;
	bool			is_dead;
	bool			full;
	bool			table_ready;
	bool			fail_thread_creation;
	pthread_t		thread_monitor;
	pthread_mutex_t	*forks;//pointer para array de garfos na mesa
	pthread_mutex_t	check;
	pthread_mutex_t	monitor;
	pthread_mutex_t	print;
	pthread_mutex_t	end;
	t_philo			*philos;
}					t_table;

//parsing.c
int		correct_input(int argc, char *argv[]);
int		is_digit(int argc, char *argv[]);
int		print_correct_input(void);
int		is_valid_time(int argc, char *argv[]);
long	ft_atoi(const char *str);

//init.c
int		init_table(char *argv[], t_table *table);
int		init_mutex(t_table *table);
int		destroy_mutex(t_table *table, int i, int flag);
int		init_philos(t_table *table);

//threads.c
int		threads(t_table *table, int i);
int		join_and_clean(t_table *table);
int		threads_fail(t_table *table);
int		one_philo(char *t_die);

//routine.c
void	*routine(void *x);
void	eating(t_philo *ph, pthread_mutex_t *a_fork, pthread_mutex_t *b_fork);
void	sleeping(t_philo *philo);
void	thinking(t_philo *philo);

//utils.c
size_t	get_current_time(void);
void	ft_usleep(size_t time);
int		print(t_philo *philo, char *str, char *c);
int		print_error(int flag);

//monitoring.c
void	*monitoring(void *x);
int		is_dead(t_table *table, int i);
int		is_all_full(t_table *table);
int		dead_or_full(t_table *table);

#endif