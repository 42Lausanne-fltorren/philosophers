/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fltorren <fltorren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 18:10:21 by fltorren          #+#    #+#             */
/*   Updated: 2024/05/30 18:10:22 by fltorren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_eating(t_philo *philo)
{
	return (get_time() - philo->last_meal <= philo->time_to_eat);
}

int	is_sleeping(t_philo *philo)
{
	if (is_eating(philo))
		return (0);
	return ((get_time() - philo->last_meal
			<= philo->time_to_eat + philo->time_to_sleep));
}

int	is_thinking(t_philo *philo)
{
	return (!is_eating(philo) && !is_sleeping(philo));
}

int	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
	{
		write(STDERR_FILENO, "Error: gettimeofday\n", 19);
		return (-1);
	}
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
