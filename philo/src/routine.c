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
	if (is_dead(philo))
	{
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	print_status(philo, "has taken a fork", 1);
	if (philo->philos_count == 1)
	{
		ft_usleep(philo->time_to_die);
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, "has taken a fork", 1);
	print_status(philo, "is eating", 1);
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->meal_lock);
	ft_usleep((int) philo->time_to_eat);
	print_status(philo, "is done eating", 1);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

static void	ft_sleep(t_philo *philo)
{
	print_status(philo, "is sleeping", 1);
	ft_usleep((int) philo->time_to_sleep);
}

static void	ft_think(t_philo *philo)
{
	print_status(philo, "is thinking", 1);
}

void	*routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (1)
	{
		if (is_dead(philo))
			break ;
		ft_eat(philo);
		pthread_mutex_lock(&philo->meal_lock);
		philo->meal++;
		pthread_mutex_unlock(&philo->meal_lock);
		if (is_dead(philo))
			break ;
		ft_sleep(philo);
		if (is_dead(philo))
			break ;
		ft_think(philo);
	}
	return (ptr);
}
