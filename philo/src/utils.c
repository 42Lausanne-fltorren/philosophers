/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fltorren <fltorren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 18:10:21 by fltorren          #+#    #+#             */
/*   Updated: 2024/06/11 16:47:23 by fltorren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
	{
		write(STDERR_FILENO, "Error: gettimeofday\n", 19);
		return (-1);
	}
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_usleep(int milliseconds)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < (size_t) milliseconds)
		usleep(500);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	res;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * sign);
}

void	print_status(t_philo *philo, char *status, int check_death)
{
	size_t	time;

	if (check_death && is_dead(philo))
		return ;
	time = get_time() - philo->start_time;
	printf("%zu %d %s\n", time, (int) philo->id, status);
}

void	free_philos(t_philo *philos, int n)
{
	if (!philos)
		return ;
	while (n >= 0)
	{
		pthread_mutex_destroy(&philos[n].meal_lock);
		n--;
	}
	free(philos);
}
