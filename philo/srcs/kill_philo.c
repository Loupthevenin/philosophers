/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 16:27:10 by ltheveni          #+#    #+#             */
/*   Updated: 2024/12/31 16:27:53 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	set_kill_philo(t_philo *head, int time)
{
	t_philo	*current;

	current = head;
	while (current)
	{
		pthread_mutex_lock(current->print_mutex);
		printf("%d %d died\n", time, current->id);
		pthread_mutex_unlock(current->print_mutex);
		current->kill_philo = 1;
		if (current->next == head)
			break ;
		current = current->next;
	}
}

static int	check_food(t_philo *head)
{
	t_philo	*current;
	int		count;
	int		max_eat;

	current = head;
	count = 0;
	max_eat = head->arg_philo.is_count_eat;
	while (current)
	{
		if (current->times_eaten >= max_eat)
		{
			if (!current->kill_philo)
				current->kill_philo = 1;
			count++;
		}
		if (current->next == head)
			break ;
		current = current->next;
	}
	return (count);
}

void	kill_philo(t_philo *philo)
{
	int	time;
	int	time_to_die;
	int	start_time;

	start_time = philo->arg_philo.start_time;
	time_to_die = philo->arg_philo.time_to_die;
	while (1)
	{
		time = get_time() - start_time;
		if (time > time_to_die)
		{
			set_kill_philo(philo, time);
			break ;
		}
		if (philo->arg_philo.is_count_eat != -1)
		{
			if (check_food(philo) == philo->arg_philo.number_of_philosophers)
				break ;
		}
	}
}
