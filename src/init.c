/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 19:37:17 by fvizcaya          #+#    #+#             */
/*   Updated: 2025/03/19 19:49:33 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_alloc_data_structs(t_dinner *dinner)
{
	dinner->forks = (pthread_mutex_t *) malloc (dinner->args->num_philos * \
		sizeof (pthread_mutex_t));
	if (!dinner->forks)
		return (-1);
	dinner->philos = (t_philo *) malloc (dinner->args->num_philos * \
					sizeof (t_philo));
	if (!dinner->philos)
		return (-1);
	return (0);
}

static void	ft_set_fork_numbers(t_philo *philo)
{
	philo->l_fork = philo->id;
	philo->r_fork = (philo->id + 1) % philo->dinner->args->num_philos;
	if ((philo->id % 2) && !(philo->dinner->args->num_philos % 2))
	{
		philo->l_fork = (philo->id + 1) % philo->dinner->args->num_philos;
		philo->r_fork = philo->id;
	}
	printf("El philo %d tiene asignados los tenedores %d y %d\n", philo->id + 1, \
		philo->l_fork + 1, philo->r_fork + 1);
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
		printf("INit: last_meal_time: %ld\n", dinner->philos[i].last_meal_time);
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
	int i;

	i = 0;
	if (ft_alloc_data_structs(dinner) == -1)
		return (perror("ERROR"), -1);
	dinner->end_of_dinner = false;
	ft_init_philos(dinner);
	while (i < dinner->args->num_philos)
		if (pthread_mutex_init(&dinner->forks[i++], NULL) != 0)
			return (-1);
	if (pthread_mutex_init(&dinner->mutex_eating, NULL) != 0 || \
		pthread_mutex_init(&dinner->mutex_time, NULL) != 0 || \
		pthread_mutex_init(&dinner->mutex_dead, NULL) != 0 || \
		pthread_mutex_init(&dinner->mutex_end, NULL) != 0 || \
		pthread_mutex_init(&dinner->mutex_stdout, NULL) != 0 )
		return (-1);
	if (ft_create_threads(dinner) != 0)
		return (-1); 
	return (0);
}
