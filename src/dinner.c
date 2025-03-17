/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 19:20:17 by fvizcaya          #+#    #+#             */
/*   Updated: 2025/03/17 22:16:10 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_philo_dead(t_dinner *dinner)
{
	int		i;
	time_t	curr_time;
	time_t	last_meal_time;

	i = 0;
	curr_time = ft_get_current_time();
	while (i < dinner->args->num_philos)
	{
		pthread_mutex_lock(&dinner->mutex_time);
		last_meal_time = dinner->philos[i].last_meal_time;
		pthread_mutex_unlock(&dinner->mutex_time);
		if ((curr_time - last_meal_time) > \
			(time_t)dinner->args->time_to_die)
		{
			printf("El philo %ld > %d\n", (curr_time - last_meal_time), dinner->args->time_to_die);
			ft_print_status(&dinner->philos[i], dead);
			pthread_mutex_lock(&dinner->mutex_end);
			dinner->end_of_dinner = true;
			pthread_mutex_unlock(&dinner->mutex_end);
			break ;
		}
		i++;
	}
}

static void	ft_num_meals_reached(t_dinner *dinner)
{
	int		i;

	if (dinner->args->times_must_eat == -1)
		return ;
	i = 0;
	while (i < dinner->args->num_philos)
	{
		pthread_mutex_lock(&dinner->mutex_eating);
		if (dinner->philos[i].num_meals < dinner->args->times_must_eat)
		{
			pthread_mutex_unlock(&dinner->mutex_eating);
			return ;
		}
		pthread_mutex_unlock(&dinner->mutex_eating);
		i++;
	}
	pthread_mutex_lock(&dinner->mutex_end);
	dinner->end_of_dinner = true;
	pthread_mutex_unlock(&dinner->mutex_end);
}

void	ft_dinner(t_dinner *dinner)
{
	while (true)
	{
		ft_philo_dead(dinner);
		ft_num_meals_reached(dinner);
		if (dinner->end_of_dinner)
			break ;
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
	pthread_mutex_destroy(&dinner->mutex_stdout);
/* 	free (dinner->philos);
	free (dinner->forks);
	free (dinner->args);
	free (dinner); */
}
