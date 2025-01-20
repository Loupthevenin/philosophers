/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 20:39:38 by ltheveni          #+#    #+#             */
/*   Updated: 2025/01/20 10:03:03 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

static void	take_fork(t_philo *philo, int one_philo)
{
	if (one_philo)
	{
		pthread_mutex_lock(&philo->fork);
		pthread_mutex_lock(philo->print_mutex);
		printf("%d %d has taken a fork\n", (int)(get_time()
				- philo->arg_philo.start_time), philo->id);
		pthread_mutex_unlock(philo->print_mutex);
		return ;
	}
	if (philo->id < philo->next->id)
	{
		pthread_mutex_lock(&philo->fork);
		print_fork(philo);
		pthread_mutex_lock(&philo->next->fork);
		print_fork(philo);
	}
	else
	{
		pthread_mutex_lock(&philo->next->fork);
		print_fork(philo);
		pthread_mutex_lock(&philo->fork);
		print_fork(philo);
	}
}

static void	down_fork(t_philo *philo, int one_philo)
{
	if (one_philo)
	{
		pthread_mutex_unlock(&philo->fork);
		return ;
	}
	if (philo->id < philo->next->id)
	{
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&philo->next->fork);
	}
	else
	{
		pthread_mutex_unlock(&philo->next->fork);
		pthread_mutex_unlock(&philo->fork);
	}
}

void	philo_eat(t_philo *philo)
{
	int	time;

	if (philo->arg_philo.number_of_philosophers == 1)
	{
		take_fork(philo, 1);
		down_fork(philo, 1);
		ft_usleep(philo->arg_philo.time_to_die + 10);
		return ;
	}
	time = (int)(get_time() - philo->arg_philo.start_time);
	pthread_mutex_lock(philo->print_mutex);
	if (!is_philo_killed(philo))
		printf("%d %d is eating\n", time, philo->id);
	pthread_mutex_unlock(philo->print_mutex);
	take_fork(philo, 0);
	set_value_meal(philo, time);
	ft_usleep(philo->arg_philo.time_to_eat);
	pthread_mutex_lock(&philo->lock_eaten);
	philo->times_eaten++;
	pthread_mutex_unlock(&philo->lock_eaten);
	pthread_mutex_lock(&philo->lock_meal);
	philo->last_meal_time = (int)(get_time() - philo->arg_philo.start_time);
	pthread_mutex_unlock(&philo->lock_meal);
	down_fork(philo, 0);
}

void	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(philo->print_mutex);
	if (!is_philo_killed(philo))
		printf("%d %d is sleeping\n", (int)(get_time()
				- philo->arg_philo.start_time), philo->id);
	pthread_mutex_unlock(philo->print_mutex);
	ft_usleep(philo->arg_philo.time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	pthread_mutex_lock(philo->print_mutex);
	if (!is_philo_killed(philo))
		printf("%d %d is thinking\n", (int)(get_time()
				- philo->arg_philo.start_time), philo->id);
	pthread_mutex_unlock(philo->print_mutex);
}
