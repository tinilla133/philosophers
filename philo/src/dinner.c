/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 19:20:17 by fvizcaya          #+#    #+#             */
/*   Updated: 2025/04/01 21:18:42 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_end(t_dinner *dinner)
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
			(time_t)dinner->args->time_to_die)
		{
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
	int		num_meals;
	t_bool	must_end;

	if (dinner->args->times_must_eat == -1)
		return ;
	i = 0;
	must_end = true;
	while (i < dinner->args->num_philos)
	{
		pthread_mutex_lock(&dinner->mutex_eating);
		num_meals = dinner->philos[i].num_meals;
		pthread_mutex_unlock(&dinner->mutex_eating);
		if (num_meals < dinner->args->times_must_eat)
			must_end = false ;
		i++;
	}
	if (must_end)
	{
		pthread_mutex_lock(&dinner->mutex_end);
		dinner->end_of_dinner = true;
		pthread_mutex_unlock(&dinner->mutex_end);
	}
}

void	ft_dinner(t_dinner *dinner)
{
	while (true)
	{
		ft_num_meals_reached(dinner);
		ft_philo_dead(dinner);
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
		pthread_join(dinner->philos[i++].thread, NULL);
	i = 0;
	while (i < dinner->args->num_philos)
		pthread_mutex_destroy(&dinner->forks[i++]);
	pthread_mutex_destroy(&dinner->mutex_eating);
	pthread_mutex_destroy(&dinner->mutex_time);
	pthread_mutex_destroy(&dinner->mutex_end);
	pthread_mutex_destroy(&dinner->mutex_stdout);
}
