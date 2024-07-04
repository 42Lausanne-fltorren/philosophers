/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fltorren <fltorren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:35:59 by fltorren          #+#    #+#             */
/*   Updated: 2024/06/11 16:47:35 by fltorren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_deaths(t_data *data)
{
	int	i;

	if (!data->philos)
		return (1);
	i = -1;
	while (++i < data->n)
	{
		if (is_dead(&data->philos[i]))
		{
			return (1);
		}
	}
	return (0);
}

int	check_meals(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n)
	{
		pthread_mutex_lock(&data->philos[i].meal_lock);
		if (data->philos[i].meal > data->must_eat && data->must_eat != -1)
		{
			pthread_mutex_unlock(&data->philos[i].meal_lock);
			return (1);
		}
		pthread_mutex_unlock(&data->philos[i].meal_lock);
	}
	return (0);
}

void	*monitor(void *pointer)
{
	t_data	*data;

	data = (t_data *)pointer;
	while (check_deaths(data) == 0 && check_meals(data) == 0)
		;
	return (data->philos);
}

int	init_monitor(t_philo *philos, t_data *d, pthread_mutex_t *f, pthread_t *m)
{
	int	i;

	pthread_mutex_init(&d->dead_lock, NULL);
	pthread_mutex_init(&d->print_lock, NULL);
	d->dead = 0;
	d->start_time = get_time();
	d->philos = philos;
	i = -1;
	while (++i < d->n)
		philos[i] = init_philo(i, d, f);
	if (pthread_create(m, NULL, monitor, d) != 0)
	{
		free(philos);
		return (1);
	}
	i = -1;
	while (++i < d->n)
		pthread_create(&philos[i].thread, NULL, &routine, &philos[i]);
	return (0);
}

void	start_monitor(t_data *data, pthread_mutex_t *forks)
{
	t_philo			*philos;
	pthread_t		manager;
	int				i;

	philos = malloc(sizeof(t_philo) * data->n);
	if (!philos)
		return ;
	if (init_monitor(philos, data, forks, &manager))
	{
		free_philos(philos, data->n);
		return ;
	}
	i = -1;
	while (++i < data->n)
		pthread_join(philos[i].thread, NULL);
	pthread_join(manager, NULL);
	free_philos(philos, data->n);
	pthread_mutex_destroy(&data->dead_lock);
	pthread_mutex_destroy(&data->print_lock);
}
