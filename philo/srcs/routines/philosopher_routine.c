/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_routine.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 19:32:03 by ltheveni          #+#    #+#             */
/*   Updated: 2025/01/01 18:10:53 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

static int	choice_start(int id, int number_of_philosophers)
{
	if (number_of_philosophers == 1)
		return (2);
	if (id % 2 == 0)
		return (2);
	else
		return (0);
}

int	is_philo_killed(t_philo *philo)
{
	int	result;

	pthread_mutex_lock(&philo->lock);
	result = philo->kill_philo;
	pthread_mutex_unlock(&philo->lock);
	return (result);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;
	int		flag_routines;

	philo = (t_philo *)arg;
	flag_routines = choice_start(philo->id,
									philo->arg_philo.number_of_philosophers);
	while (!is_philo_killed(philo))
	{
		if (flag_routines == 2)
		{
			philo_eat(philo);
			flag_routines = 1;
		}
		else if (flag_routines == 1)
		{
			philo_sleep(philo);
			flag_routines = 0;
		}
		else
		{
			philo_think(philo);
			flag_routines = 2;
		}
	}
	return (NULL);
}
