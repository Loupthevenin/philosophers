/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_food.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 11:12:28 by ltheveni          #+#    #+#             */
/*   Updated: 2025/01/18 16:47:21 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int	check_food(t_philo *philo, int max_eat)
{
	int	times_eaten;
	int	simulation_end;

	pthread_mutex_lock(&philo->lock);
	times_eaten = philo->times_eaten;
	pthread_mutex_unlock(&philo->lock);
	if (times_eaten >= max_eat)
	{
		pthread_mutex_lock(&philo->arg_philo.simulation_lock);
		simulation_end = philo->arg_philo.simulation_end;
		pthread_mutex_unlock(&philo->arg_philo.simulation_lock);
		if (!simulation_end)
			set_all_kill_philo(philo);
		return (1);
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
