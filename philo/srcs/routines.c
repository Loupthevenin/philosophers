/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 20:39:38 by ltheveni          #+#    #+#             */
/*   Updated: 2024/12/31 16:24:33 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	take_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	pthread_mutex_lock(&philo->next->fork);
	pthread_mutex_lock(philo->print_mutex);
	printf("%d %d has taken a fork\n", (int)(get_time()
				- philo->arg_philo.start_time), philo->id);
	pthread_mutex_unlock(philo->print_mutex);
}

static void	down_fork(t_philo *philo)
{
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->next->fork);
}

// socrate reste coincé ici ! help!
void	philo_eat(t_philo *philo)
{
	take_fork(philo);
	pthread_mutex_lock(philo->print_mutex);
	printf("%d %d is eating\n", (int)(get_time() - philo->arg_philo.start_time),
			philo->id);
	pthread_mutex_unlock(philo->print_mutex);
	philo->times_eaten++;
	usleep(philo->arg_philo.time_to_eat * 1000);
	down_fork(philo);
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
