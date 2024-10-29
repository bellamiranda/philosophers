/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismirand <ismirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:55:10 by ismirand          #+#    #+#             */
/*   Updated: 2024/10/24 16:28:22 by ismirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	main(int argc, char *argv[])
{
	t_table	table;

	if (!correct_input(argc, argv))
		return (print_correct_input());
	if (ft_atoi(argv[1]) == 1)
		return (one_philo(argv[2]));
	if (init_table(argv, &table))
		return (print_error(5));
	if (threads(&table, -1))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/* 
./philo 199 601 200 100 -> nao morre
 */