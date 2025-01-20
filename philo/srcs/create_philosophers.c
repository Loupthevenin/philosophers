/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philosophers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 11:59:14 by ltheveni          #+#    #+#             */
/*   Updated: 2025/01/20 08:58:11 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	print_meal(t_philo *philo)
{
	int	i;
	int	required_meals;
	int	all_ok;

	i = 0;
	all_ok = 1;
	required_meals = philo->arg_philo.nb_meals;
	while (i < philo->arg_philo.number_of_philosophers)
	{
		if (philo->times_eaten < required_meals)
			all_ok = 0;
		philo = philo->next;
		i++;
	}
	if (all_ok)
		printf("Each philosopher ate %d time(s)\n", required_meals);
	else
		printf("Not all philosopher ate %d time(s)\n", required_meals);
}

static void	cleanup_philo(t_philo *head, int n)
{
	t_philo	*current;
	t_philo	*tmp;
	int		i;

	current = head;
	i = 0;
	while (i < n)
	{
		tmp = current;
		current = current->next;
		pthread_mutex_destroy(&tmp->fork);
		pthread_mutex_destroy(&tmp->lock);
		free(tmp);
		i++;
		if (current == head)
			break ;
	}
	pthread_mutex_destroy(&tmp->arg_philo.simulation_lock);
	pthread_mutex_destroy(tmp->print_mutex);
}

static void	create_thread(t_philo *head, int n)
{
	t_philo		*current;
	int			i;
	pthread_t	*philo_thread;
	pthread_t	kill_threads;

	i = 0;
	current = head;
	philo_thread = (pthread_t *)malloc(sizeof(pthread_t) * n);
	if (!philo_thread)
		return ;
	while (i < n)
	{
		pthread_create(&philo_thread[i], NULL, philosopher_routine, current);
		current = current->next;
		i++;
	}
	pthread_create(&kill_threads, NULL, kill_philo, head);
	i = 0;
	while (i < n)
	{
		pthread_join(philo_thread[i], NULL);
		i++;
	}
	pthread_join(kill_threads, NULL);
	free(philo_thread);
}

void	create_philosophers(t_arg_philo arg_philo)
{
	t_philo			*philo;
	pthread_mutex_t	print_mutex;

	pthread_mutex_init(&print_mutex, NULL);
	philo = init_philo(arg_philo, &print_mutex);
	create_thread(philo, philo->arg_philo.number_of_philosophers);
	if (philo->arg_philo.nb_meals != -1)
		print_meal(philo);
	cleanup_philo(philo, philo->arg_philo.number_of_philosophers);
}
