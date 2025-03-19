/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 19:20:17 by fvizcaya          #+#    #+#             */
/*   Updated: 2025/03/19 21:50:28 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_end_flag(t_dinner *dinner)
{
	pthread_mutex_lock(&dinner->mutex_end);
	if (dinner->end_of_dinner)
	{
		pthread_mutex_unlock(&dinner->mutex_end);
		return (-1);
	}
	pthread_mutex_unlock(&dinner->mutex_end);
	return (0);
}

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
			(time_t) dinner->args->time_to_die)
		{
			pthread_mutex_lock(&dinner->mutex_end);
			dinner->end_of_dinner = true;
			pthread_mutex_unlock(&dinner->mutex_end);
			ft_print_status(&dinner->philos[i], dead);
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
}
