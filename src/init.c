/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 19:37:17 by fvizcaya          #+#    #+#             */
/*   Updated: 2025/03/21 00:48:39 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_set_fork_numbers(t_philo *philo)
{
	int	num_philos;

	num_philos = philo->dinner->args->num_philos;
	philo->l_fork = philo->id;
	philo->r_fork = (philo->id + 1) % num_philos;
	if ((philo->id % 2))
	{
		philo->l_fork = (philo->id + 1) % num_philos;
		philo->r_fork = philo->id;
	}
}

static void	ft_init_philos(t_dinner *dinner)
{
	int	i;

	i = 0;
	while (i < dinner->args->num_philos)
	{
		dinner->philos[i].id = i;
		dinner->philos[i].dead = false;
		dinner->philos[i].last_meal_time = ft_get_current_time();
		dinner->philos[i].num_meals = 0;
		dinner->philos[i].dinner = dinner;
		ft_set_fork_numbers(&dinner->philos[i]);
		i++;
	}
}

static int	ft_create_threads(t_dinner *dinner)
{
	int	i;

	i = 0;
	while (i < dinner->args->num_philos)
	{
		if (pthread_create(&dinner->philos[i].thread, \
						NULL, ft_philo, &dinner->philos[i]) != 0)
			return (-1);
		i++;
	}
	return (0);
}

int	ft_init(t_dinner *dinner)
{
	int	i;

	i = 0;
	dinner->end_of_dinner = false;
	ft_init_philos(dinner);
	while (i < dinner->args->num_philos)
		if (pthread_mutex_init(&dinner->forks[i++], NULL) != 0)
			return (-1);
	if (pthread_mutex_init(&dinner->mutex_eating, NULL) != 0 || \
		pthread_mutex_init(&dinner->mutex_time, NULL) != 0 || \
		pthread_mutex_init(&dinner->mutex_end, NULL) != 0 || \
		pthread_mutex_init(&dinner->mutex_stdout, NULL) != 0)
		return (-1);
	if (ft_create_threads(dinner) != 0)
		return (-1);
	return (0);
}
