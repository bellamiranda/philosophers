/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismirand <ismirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:55:10 by ismirand          #+#    #+#             */
/*   Updated: 2024/10/11 15:08:28 by ismirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	main(int argc, char *argv[])
{
	t_table	table;

	if (!correct_input(argc, argv))
		return (print_correct_input());
	if (init_table(argv, &table))
		return (EXIT_FAILURE);
	if (threads(&table))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
