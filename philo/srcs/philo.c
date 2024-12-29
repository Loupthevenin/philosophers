/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 19:42:54 by ltheveni          #+#    #+#             */
/*   Updated: 2024/12/29 20:58:43 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	check_args(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!is_digit(argv[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	init_args(t_arg_philo *arg_philo, int argc, char **argv)
{
	arg_philo->number_of_philosophers = ft_atoi(argv[1]);
	arg_philo->time_to_die = ft_atoi(argv[2]);
	arg_philo->time_to_eat = ft_atoi(argv[3]);
	arg_philo->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 5)
		arg_philo->is_count_eat = -1;
	else
		arg_philo->is_count_eat = ft_atoi(argv[5]);
}

int	main(int argc, char **argv)
{
	t_arg_philo	arg_philo;

	if (argc == 5 || argc == 6)
	{
		if (!check_args(argc, argv))
			return (1);
		init_args(&arg_philo, argc, argv);
	}
	else
		return (1);
	return (0);
}
