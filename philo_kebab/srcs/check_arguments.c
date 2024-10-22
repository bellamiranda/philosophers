/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malves-b <malves-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:02:21 by malves-b          #+#    #+#             */
/*   Updated: 2024/10/03 16:17:17 by malves-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	check_arg(char **argv, int argc, int j)
{
	int	i;

	i = 1;
	if (ft_atoi(argv[1]) == 0)
		printf("\033[31mAmount of philo should be at least %i\n\033[0m", ++j);
	if (ft_atoi(argv[1]) > 200)
		printf("\033[31mAmount of philo is more than %i\n\033[0m", ++j + 199);
	if (j > 0)
		return (1);
	while (i < argc)
	{
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
			{
				printf("\033[31mYour %iº argument contain char!\033[0m\n", i);
				return (2);
			}
			j++;
		}
		i++;
		j = 0;
	}
	return (0);
}
