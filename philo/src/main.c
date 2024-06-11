/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fltorren <fltorren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 18:10:25 by fltorren          #+#    #+#             */
/*   Updated: 2024/06/11 16:40:23 by fltorren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_forks(pthread_mutex_t *forks, int n)
{
	int	i;

	i = 0;
	while (i < n)
		pthread_mutex_destroy(&forks[i++]);
	free(forks);
}

pthread_mutex_t	*init_forks(int n)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = malloc(sizeof(pthread_mutex_t) * n);
	if (!forks)
		return (NULL);
	i = -1;
	while (++i < n)
		pthread_mutex_init(&forks[i], NULL);
	return (forks);
}

static int	parse_data(t_data *data, int argc, char **argv)
{
	data->n = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (data->n < 1 || data->time_to_die < 1 || data->time_to_eat < 1
		|| data->time_to_sleep < 1)
	{
		printf("Error: arguments must be positive integers\n");
		return (0);
	}
	if (argc == 6)
	{
		data->must_eat = ft_atoi(argv[5]);
		if (data->must_eat < 1)
		{
			printf("Error: arguments must be positive integers\n");
			return (0);
		}
	}
	else
		data->must_eat = -1;
	return (1);
}

int	main(int argc, char **argv)
{
	pthread_mutex_t	*forks;
	t_data			data;

	if (argc != 5 && argc != 6)
	{
		printf("Error: wrong number of arguments\n");
		return (1);
	}
	if (!parse_data(&data, argc, argv))
		return (1);
	forks = init_forks(data.n);
	if (!forks)
		return (1);
	start_monitor(&data, forks);
	free_forks(forks, data.n);
	return (0);
}
