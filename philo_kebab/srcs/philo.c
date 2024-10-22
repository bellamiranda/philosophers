/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malves-b <malves-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 13:35:47 by malves-b          #+#    #+#             */
/*   Updated: 2024/10/10 16:06:25 by malves-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	main(int argc, char **argv)
{
	t_exe	*start;

	if (ft_aux(argc, argv))
		return (1);
	start = malloc(sizeof(t_exe));
	if (!start)
	{
		puts("\033[31mError malloc struct t_exe *main*\033[0m");
		return (1);
	}
	if (argc == 6)
		start->target_eat = ft_atoi(argv[5]);
	else
		start->target_eat = -5;
	if (init_threads(start, argv) != 0)
	{
		clean_program(start);
		return (1);
	}
	if (monitor_philos(start))
	{
		clean_program(start);
		return (1);
	}
	return (0);
}

int	ft_aux(int argc, char **argv)
{
	size_t	start_time;

	if (argc != 6 && argc != 5)
	{
		puts("\033[31mBad argument!\033[0m");
		return (1);
	}
	if (ft_atoi(argv[1]) == 1)
	{
		start_time = get_current_time();
		usleep(ft_atoi(argv[2]) * 1000);
		printf("\033[31m%lu ", get_current_time() - start_time);
		printf("\033[31mPhilo 1 died\n\033[0m");
		return (1);
	}
	if (check_arg(argv, argc, 0))
		return (1);
	if (ft_atoi(argv[5]) == 0)
		return (1);
	return (0);
}
