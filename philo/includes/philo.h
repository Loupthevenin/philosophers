/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 19:39:40 by ltheveni          #+#    #+#             */
/*   Updated: 2024/12/30 18:46:57 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_arg_philo
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				is_count_eat;
}					t_arg_philo;

typedef struct s_philo
{
	int				id;
	t_arg_philo		arg_philo;
	pthread_mutex_t	fork;
	pthread_mutex_t	*print_mutex;
	struct s_philo	*next;
}					t_philo;

int					is_digit(const char *s);
int					ft_atoi(char *str);
void				init_args(t_arg_philo *arg_philo, int argc, char **argv);
t_philo				*init_philo(t_arg_philo arg_philo, pthread_mutex_t *mutex);

void				create_philosophers(t_arg_philo arg_philo);

#endif
