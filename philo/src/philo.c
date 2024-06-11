/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fltorren <fltorren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:36:23 by fltorren          #+#    #+#             */
/*   Updated: 2024/06/11 16:47:46 by fltorren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead)
	{
		pthread_mutex_unlock(philo->dead_lock);
		return (1);
	}
	if (get_time() - philo->last_meal >= (size_t) philo->time_to_die)
	{
		*philo->dead = 1;
		print_status(philo, "died");
		pthread_mutex_unlock(philo->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

t_philo	init_philo(int id, t_data *data, pthread_mutex_t *forks)
{
	t_philo	philo;

	philo.id = id;
	philo.time_to_die = data->time_to_die;
	philo.time_to_eat = data->time_to_eat;
	philo.time_to_sleep = data->time_to_sleep;
	philo.last_meal = get_time();
	philo.dead = &data->dead;
	philo.meal = 0;
	philo.dead_lock = &data->dead_lock;
	philo.start_time = data->start_time;
	pthread_mutex_init(&philo.meal_lock, NULL);
	philo.right_fork = &forks[id];
	if ((int) id == 0)
		philo.left_fork = &forks[data->n - 1];
	else
		philo.left_fork = &forks[id - 1];
	return (philo);
}
