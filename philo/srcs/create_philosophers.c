/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philosophers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 11:59:14 by ltheveni          #+#    #+#             */
/*   Updated: 2024/12/30 18:59:45 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/* static void	print_philo(t_philo *head) */
/* { */
/* 	t_philo	*current; */
/**/
/* 	current = head; */
/* 	while (current) */
/* 	{ */
/* 		printf("Philosophers id :%d\n", current->id); */
/* 		if (current->next == head) */
/* 			break ; */
/* 		current = current->next; */
/* 	} */
/* } */

static void	cleanup_philo(t_philo *head, int n)
{
	t_philo	*current;
	t_philo	*tmp;
	int		i;

	pthread_mutex_destroy(head->print_mutex);
	current = head;
	i = 0;
	while (i < n)
	{
		tmp = current;
		current = current->next;
		pthread_mutex_destroy(&tmp->fork);
		free(tmp);
		i++;
	}
}

void	create_philosophers(t_arg_philo arg_philo)
{
	t_philo			*philo;
	pthread_mutex_t	print_mutex;

	pthread_mutex_init(&print_mutex, NULL);
	philo = init_philo(arg_philo, &print_mutex);
	cleanup_philo(philo, philo->arg_philo.number_of_philosophers);
}
