/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismirand <ismirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:55:10 by ismirand          #+#    #+#             */
/*   Updated: 2024/10/22 14:54:03 by ismirand         ###   ########.fr       */
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
ERROS:
philo: pthread_mutex_lock.c:94: ___pthread_mutex_lock: Assertion `mutex->__data.__owner == 0' failed.
zsh: IOT instruction (core dumped)  ./philo 4 200 205 200

philo: pthread_mutex_lock.c:94: ___pthread_mutex_lock: Assertion `mutex->__data.__owner == 0' failed.
1729522300032 1 has taken a fork
1 1 has taken a fork
1 1 is eating
zsh: IOT instruction (core dumped)  ./philo 4 200 205 200


 */