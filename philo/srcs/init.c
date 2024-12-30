/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 12:45:43 by ltheveni          #+#    #+#             */
/*   Updated: 2024/12/30 18:49:14 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static t_philo	*set_new_philo(t_arg_philo arg_philo,
								pthread_mutex_t *print_mutex,
								int i)
{
	t_philo	*new_philo;

	new_philo = (t_philo *)malloc(sizeof(t_philo));
	if (!new_philo)
		return (NULL);
	new_philo->id = i + 1;
	new_philo->arg_philo = arg_philo;
	pthread_mutex_init(&new_philo->fork, NULL);
	new_philo->print_mutex = print_mutex;
	new_philo->next = NULL;
	return (new_philo);
}

void	init_args(t_arg_philo *arg_philo, int argc, char **argv)
{
	arg_philo->number_of_philosophers = ft_atoi(argv[1]);
	arg_philo->time_to_die = ft_atoi(argv[2]);
	arg_philo->time_to_eat = ft_atoi(argv[3]);
	arg_philo->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 5)
		arg_philo->is_count_eat = -1;
	else
		arg_philo->is_count_eat = ft_atoi(argv[5]);
}

t_philo	*init_philo(t_arg_philo arg_philo, pthread_mutex_t *print_mutex)
{
	int		i;
	t_philo	*head;
	t_philo	*current;
	t_philo	*new_philo;

	head = NULL;
	current = NULL;
	i = 0;
	while (i < arg_philo.number_of_philosophers)
	{
		new_philo = set_new_philo(arg_philo, print_mutex, i);
		if (!head)
			head = new_philo;
		else
			current->next = new_philo;
		current = new_philo;
		i++;
	}
	if (current)
		current->next = head;
	return (head);
}
