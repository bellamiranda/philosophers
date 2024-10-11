/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismirand <ismirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:02:37 by ismirand          #+#    #+#             */
/*   Updated: 2024/10/10 16:40:06 by ismirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/*
Checks if it has less than 5 or more than 6 arguments
Checks if all arguments are numbers
Checks if all the arguments have valid times
Returns 1 if anything is invalid
*/
int	correct_input(int argc, char *argv[])
{
	if (argc < 5 || argc > 6)
		return (false);
	if (!is_digit(argc, argv))
		return (false);
	if (!is_valid_time(argc, argv))
		return (false);
	return (true);
}

/*
Returns 0 if one of the arguments is not a number
*/
int	is_digit(int argc, char *argv[])
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

//prints how to write a correct input
//Returns 1 for the incorrect input return
int	print_correct_input(void)
{
	printf(RED"!!WRONG INPUT!!\n"RESET);
	printf(GREEN"TRY THIS:\n"RESET);
	printf("  ./philo nb_philos time_to_die time_to_eat time_to_sleep ");
	printf("nb_meals(optional)\n");
	printf(CYAN"INSTRUCTIONS:\n"RESET);
	printf("  1 < nb_philos < 200\n");
	printf("  60 <= time_to_die <= INT_MAX\n");
	printf("  60 <= time_to_eat <= INT_MAX\n");
	printf("  60 <= time_to_sleep <= INT_MAX\n");
	printf("  0 < number_of_times_each_philosopher_must_eat < INT_MAX\n");
	printf(RED" * INT_MAX = 2147483647!!!\n"RESET);
	return (true);
}

/*
Checks if the num of meals is positive
Checks if the num of philos is between 1 and 200
Checks if the times are equal or bigger than 60
Returns 1 if anything is invalid
*/
int	is_valid_time(int argc, char *argv[])
{
	int	i;

	i = 1;
	if (argc == 6 && (ft_atoi(argv[5]) <= 0 || ft_atoi(argv[5]) > INT_MAX))
		return (false);
	if (ft_atoi(argv[1]) < 1 || ft_atoi(argv[1]) > 200)
		return (false);
	while (++i < 5)
		if (ft_atoi(argv[i]) < 60 || ft_atoi(argv[i]) > INT_MAX)
			return (false);
	return (true);
}

long	ft_atoi(const char *str)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	while ((str[i] == '-' || str[i] == '+') && \
		(str[i + 1] >= '0' && str[i + 1] <= '9'))
	{
		if (str[i] == '-')
			k = k * (-1);
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		j = j * 10 + str[i] - '0';
		i++;
	}
	return (j * k);
}
