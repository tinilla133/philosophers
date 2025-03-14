/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 19:20:17 by fvizcaya          #+#    #+#             */
/*   Updated: 2025/03/04 18:47:58 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_bool	ft_philo_dead(t_dinner *dinner)
{
	int		i;
	int		curr_time;

	i = 0;
	curr_time = ft_get_current_time();
	pthread_mutex_lock(&dinner->mutex_time);
	while (i < dinner->args->num_philos)
	{
		if ((curr_time - dinner->philos[i].last_meal_time) > \
			dinner->args->time_to_die)
		{
			pthread_mutex_lock(&dinner->mutex_dead);
			dinner->philos[i].dead = true;
			pthread_mutex_unlock(&dinner->mutex_dead);
			ft_print_status(&dinner->philos[i], dead);
			pthread_mutex_unlock(&dinner->mutex_time);
			return (true);
		}
		i++;
	}
	pthread_mutex_unlock(&dinner->mutex_time);
	return (false);
}

static t_bool	ft_num_meals_reached(t_dinner *dinner)
{
	int		i;

	if (dinner->args->times_must_eat == -1)
		return (false);
	i = 0;
	while (i < dinner->args->num_philos)
	{
		pthread_mutex_lock(&dinner->mutex_eating);
		if (dinner->philos[i].num_meals < dinner->args->times_must_eat)
		{
			pthread_mutex_unlock(&dinner->mutex_eating);
			return (false);
		}
		pthread_mutex_unlock(&dinner->mutex_eating);
		i++;
	}
	return (true);
}

static inline t_bool	ft_end_of_dinner(t_dinner *dinner)
{
	return (ft_philo_dead(dinner) || ft_num_meals_reached(dinner));
}

void	ft_dinner(t_dinner *dinner)
{
	dinner->end_of_dinner = false;
	while (!dinner->end_of_dinner)
	{
		dinner->end_of_dinner = ft_end_of_dinner(dinner);
	}
	ft_stop_dinner(dinner);
}

void	ft_stop_dinner(t_dinner *dinner)
{
	int	i;

	printf("Entramos en ft_stop_dinner\n");
	i = 0;
	while (i < dinner->args->num_philos)
	{
		pthread_join(dinner->philos[i++].thread, NULL);
	}
	i = 0;
	while (i < dinner->args->num_philos)
	{
		pthread_mutex_destroy(&dinner->forks[i++]);
	}
	pthread_mutex_destroy(&dinner->mutex_eating);
	pthread_mutex_destroy(&dinner->mutex_time);
	pthread_mutex_destroy(&dinner->mutex_dead);
	pthread_mutex_destroy(&dinner->mutex_end);
	pthread_mutex_destroy(&dinner->std_out);
	pthread_exit(NULL);
	free (dinner->philos);
	free (dinner->forks);
	free (dinner->args);
	free (dinner);
}
