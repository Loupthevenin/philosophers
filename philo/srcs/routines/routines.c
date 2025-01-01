/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 20:39:38 by ltheveni          #+#    #+#             */
/*   Updated: 2025/01/01 18:51:06 by ltheveni         ###   ########.fr       */
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
		pthread_mutex_lock(&philo->next->fork);
	}
	else
	{
		pthread_mutex_lock(&philo->next->fork);
		pthread_mutex_lock(&philo->fork);
	}
	pthread_mutex_lock(philo->print_mutex);
	printf("%d %d has taken a fork\n", (int)(get_time()
				- philo->arg_philo.start_time), philo->id);
	pthread_mutex_unlock(philo->print_mutex);
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
		pthread_mutex_unlock(&philo->next->fork);
		pthread_mutex_unlock(&philo->fork);
	}
	else
	{
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&philo->next->fork);
	}
}

void	philo_eat(t_philo *philo)
{
	int	time;

	if (philo->arg_philo.number_of_philosophers == 1)
	{
		take_fork(philo, 1);
		down_fork(philo, 1);
		usleep(philo->arg_philo.time_to_die * 1000);
		return ;
	}
	take_fork(philo, 0);
	if (!is_philo_killed(philo))
	{
		down_fork(philo, 0);
		return ;
	}
	pthread_mutex_lock(philo->print_mutex);
	time = (int)(get_time() - philo->arg_philo.start_time);
	printf("%d %d is eating\n", time, philo->id);
	pthread_mutex_unlock(philo->print_mutex);
	pthread_mutex_lock(&philo->lock);
	philo->times_eaten++;
	philo->last_meal_time = time;
	pthread_mutex_unlock(&philo->lock);
	usleep(philo->arg_philo.time_to_eat * 1000);
	down_fork(philo, 0);
}

void	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(philo->print_mutex);
	printf("%d %d is sleeping\n", (int)(get_time()
				- philo->arg_philo.start_time), philo->id);
	pthread_mutex_unlock(philo->print_mutex);
	usleep(philo->arg_philo.time_to_sleep * 1000);
}

void	philo_think(t_philo *philo)
{
	pthread_mutex_lock(philo->print_mutex);
	printf("%d %d is thinking\n", (int)(get_time()
				- philo->arg_philo.start_time), philo->id);
	pthread_mutex_unlock(philo->print_mutex);
}
