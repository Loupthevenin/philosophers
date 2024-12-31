/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_routine.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 19:32:03 by ltheveni          #+#    #+#             */
/*   Updated: 2024/12/31 16:22:53 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// mettre en place un algo sur l'id des philo;
static int	choice_start(int id)
{
	if (id % 2 == 0)
		return (2);
	else
		return (0);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;
	int		flag_routines;

	philo = (t_philo *)arg;
	flag_routines = choice_start(philo->id);
	while (!philo->kill_philo)
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
