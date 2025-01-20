/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_food.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 11:12:28 by ltheveni          #+#    #+#             */
/*   Updated: 2025/01/20 09:18:27 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int	check_food(t_philo *philo, int max_eat)
{
	int	times_eaten;

	pthread_mutex_lock(&philo->lock_eaten);
	times_eaten = philo->times_eaten;
	pthread_mutex_unlock(&philo->lock_eaten);
	if (times_eaten >= max_eat)
	{
		pthread_mutex_lock(&philo->arg_philo.simulation_lock);
		if (!philo->arg_philo.simulation_end)
		{
			philo->arg_philo.simulation_end = 1;
			pthread_mutex_unlock(&philo->arg_philo.simulation_lock);
			return (1);
		}
		pthread_mutex_unlock(&philo->arg_philo.simulation_lock);
	}
	return (0);
}

void	set_all_kill_philo(t_philo *head)
{
	t_philo	*current;

	current = head;
	while (current)
	{
		pthread_mutex_lock(&current->arg_philo.simulation_lock);
		current->arg_philo.simulation_end = 1;
		pthread_mutex_unlock(&current->arg_philo.simulation_lock);
		current = current->next;
		if (current == head)
			return ;
	}
}

int	is_philo_all_killed(t_philo *head)
{
	t_philo	*current;
	int		simulation_end;

	current = head;
	while (1)
	{
		pthread_mutex_lock(&current->arg_philo.simulation_lock);
		simulation_end = current->arg_philo.simulation_end;
		pthread_mutex_unlock(&current->arg_philo.simulation_lock);
		if (!simulation_end)
			return (0);
		current = current->next;
		if (current == head)
			break ;
	}
	return (1);
}
