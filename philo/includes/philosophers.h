/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fltorren <fltorren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 18:10:21 by fltorren          #+#    #+#             */
/*   Updated: 2024/06/11 16:47:13 by fltorren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>

typedef struct s_philo
{
	pthread_t		thread;
	int				id;

	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				philos_count;
	size_t			start_time;

	size_t			last_meal;
	int				meal;
	pthread_mutex_t	meal_lock;
	int				*dead;
	pthread_mutex_t	*dead_lock;

	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}	t_philo;

typedef struct s_data
{
	int				n;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	int				dead;
	pthread_mutex_t	dead_lock;
	size_t			start_time;
	t_philo			*philos;
}	t_data;

int		is_dead(t_philo *philo);
t_philo	init_philo(int id, t_data *data, pthread_mutex_t *forks);
void	free_philos(t_philo *philos, int n);

size_t	get_time(void);
void	ft_usleep(int time);
int		ft_atoi(const char *str);
void	print_status(t_philo *philo, char *status, int check_death);

void	*routine(void *philo);

void	start_monitor(t_data *data, pthread_mutex_t *forks);
#endif