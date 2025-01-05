/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 20:39:38 by ltheveni          #+#    #+#             */
/*   Updated: 2025/01/05 10:38:20 by ltheveni         ###   ########.fr       */
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
	if (!is_philo_killed(philo))
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
		ft_usleep(philo->arg_philo.time_to_die);
		return ;
	}
	take_fork(philo, 0);
	pthread_mutex_lock(philo->print_mutex);
	time = (int)(get_time() - philo->arg_philo.start_time);
	if (!is_philo_killed(philo))
		printf("%d %d is eating\n", time, philo->id);
	pthread_mutex_unlock(philo->print_mutex);
	pthread_mutex_lock(&philo->lock);
	philo->times_eaten++;
	philo->last_meal_time = time;
	pthread_mutex_unlock(&philo->lock);
	ft_usleep(philo->arg_philo.time_to_eat);
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
