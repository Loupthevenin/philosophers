/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 16:27:10 by ltheveni          #+#    #+#             */
/*   Updated: 2025/01/20 09:18:11 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

static void	set_kill_philo(t_philo *philo, int time)
{
	int	simulation_end;

	pthread_mutex_lock(&philo->arg_philo.simulation_lock);
	simulation_end = philo->arg_philo.simulation_end;
	pthread_mutex_unlock(&philo->arg_philo.simulation_lock);
	if (!simulation_end)
	{
		set_all_kill_philo(philo);
		pthread_mutex_lock(philo->print_mutex);
		printf("\033[31m%d %d died\n\033[0m", time, philo->id);
		pthread_mutex_unlock(philo->print_mutex);
	}
}

static int	check_meal(t_philo *current)
{
	if (current->arg_philo.nb_meals != -1)
	{
		if (check_food(current, current->arg_philo.nb_meals))
		{
			if (is_philo_all_killed(current))
				return (1);
		}
	}
	return (0);
}

static void	kill_loop(t_philo *head, int start_time, int time_to_die)
{
	t_philo	*current;
	int		time;
	int		diff_time;
	int		simulation_end;

	current = head;
	while (1)
	{
		if (is_philo_all_killed(current))
			return ;
		time = get_time() - start_time;
		pthread_mutex_lock(&current->lock_meal);
		diff_time = time - current->last_meal_time;
		pthread_mutex_unlock(&current->lock_meal);
		pthread_mutex_lock(&current->arg_philo.simulation_lock);
		simulation_end = current->arg_philo.simulation_end;
		pthread_mutex_unlock(&current->arg_philo.simulation_lock);
		if (diff_time > time_to_die && !simulation_end)
			return (set_kill_philo(current, time));
		if (check_meal(current))
			return ;
		current = current->next;
	}
}

void	*kill_philo(void *arg)
{
	t_philo	*philo;
	int		time_to_die;
	int		start_time;

	philo = arg;
	start_time = philo->arg_philo.start_time;
	time_to_die = philo->arg_philo.time_to_die;
	kill_loop(philo, start_time, time_to_die);
	return (NULL);
}
