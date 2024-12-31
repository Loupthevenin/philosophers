/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 19:42:54 by ltheveni          #+#    #+#             */
/*   Updated: 2024/12/31 14:16:50 by ltheveni         ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	t_arg_philo	arg_philo;
	long		start_time;

	if (argc == 5 || argc == 6)
	{
		if (!check_args(argc, argv))
			return (1);
		start_time = get_time();
		init_args(&arg_philo, argc, argv, start_time);
		if (arg_philo.number_of_philosophers == 0)
			return (0);
		create_philosophers(arg_philo);
	}
	else
		return (1);
	return (0);
}
