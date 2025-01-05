/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 16:27:10 by ltheveni          #+#    #+#             */
/*   Updated: 2025/01/05 11:09:49 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

static int	check_food(t_philo *philo, int max_eat)
{
	int	times_eaten;

	pthread_mutex_lock(&philo->lock);
	times_eaten = philo->times_eaten;
	pthread_mutex_unlock(&philo->lock);
	if (times_eaten >= max_eat)
	{
		if (!philo->kill_philo)
		{
			pthread_mutex_lock(&philo->lock);
			philo->kill_philo = 1;
			pthread_mutex_unlock(&philo->lock);
			return (1);
		}
	}
	return (0);
}

static void	set_kill_philo(t_philo *philo, int time)
{
	pthread_mutex_lock(philo->print_mutex);
	printf("%d %d died\n", time, philo->id);
	pthread_mutex_unlock(philo->print_mutex);
	pthread_mutex_lock(&philo->lock);
	philo->kill_philo = 1;
	pthread_mutex_unlock(&philo->lock);
}

static void	kill_loop(t_philo *head, int start_time, int time_to_die,
		int max_count)
{
	t_philo	*current;
	int		time;
	int		diff_time;
	int		count;

	current = head;
	count = 0;
	while (count < max_count)
	{
		time = get_time() - start_time;
		pthread_mutex_lock(&current->lock);
		diff_time = time - current->last_meal_time;
		pthread_mutex_unlock(&current->lock);
		if (diff_time > time_to_die && !current->kill_philo)
		{
			set_kill_philo(current, time);
			count++;
		}
		if (current->arg_philo.nb_meals != -1)
			count += check_food(current, current->arg_philo.nb_meals);
		current = current->next;
	}
}

void	*kill_philo(void *arg)
{
	t_philo	*philo;
	int		time_to_die;
	int		start_time;
	int		max_count;

	philo = arg;
	start_time = philo->arg_philo.start_time;
	time_to_die = philo->arg_philo.time_to_die;
	max_count = philo->arg_philo.number_of_philosophers;
	kill_loop(philo, start_time, time_to_die, max_count);
	return (NULL);
}
