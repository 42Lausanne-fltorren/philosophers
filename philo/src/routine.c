/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fltorren <fltorren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 18:49:10 by fltorren          #+#    #+#             */
/*   Updated: 2024/06/11 16:40:40 by fltorren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a fork");
	if (philo->philos_count == 1)
	{
		ft_usleep(philo->time_to_die);
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, "has taken a fork");
	print_status(philo, "is eating");
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal = get_time();
	philo->meal++;
	pthread_mutex_unlock(&philo->meal_lock);
	ft_usleep((int) philo->time_to_eat);
	print_status(philo, "is done eating");
	pthread_mutex_unlock(philo->left_fork);
	print_status(philo, "has released a fork");
	pthread_mutex_unlock(philo->right_fork);
	print_status(philo, "has released a fork");
}

static void	ft_sleep(t_philo *philo)
{
	print_status(philo, "is sleeping");
	ft_usleep((int) philo->time_to_sleep);
}

static void	ft_think(t_philo *philo)
{
	print_status(philo, "is thinking");
}

void	*routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (!is_dead(philo))
	{
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
	return (ptr);
}
