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

static t_bool	ft_philo_dead(t_program *program)
{
	int		i;
	int		curr_time;
	t_bool	ret;

	i = 0;
	pthread_mutex_lock(&program->mutex_time);
	curr_time = ft_get_current_time();
	pthread_mutex_unlock(&program->mutex_time);
	ret = false;
	while (i < program->args->num_philos)
	{
		pthread_mutex_lock(&program->dinner->philos[i].mutex_time);
		if ((curr_time - program->dinner->philos[i].last_meal_time) > \
			program->args->time_to_die)
		{
			program->dinner->philos[i].status = dead;
			ret = true;
		}
		pthread_mutex_unlock(&program->dinner->philos[i].mutex_time);
		i++;
	}
	return (ret);
}

static t_bool	ft_num_meals_reached(t_program *program)
{
	int		i;
	t_bool	ret;

	if (program->args->times_must_eat == -1)
		return (false);
	i = 0;
	ret = true;
	while (i < program->args->num_philos)
	{
		pthread_mutex_lock(&program->dinner->mutex_dinner);
		if (program->dinner->philos[i].num_meals == program->args->times_must_eat)
		{
			ret = false;
		}
		pthread_mutex_unlock(&program->dinner->mutex_dinner);
		i++;
	}
	return (ret);
}

static inline t_bool	ft_end_of_dinner(t_program *program)
{
	return (ft_philo_dead(program) || ft_num_meals_reached(program));
}

void	*ft_dinner(void *ptr)
{
	t_program	*program;

	program = (t_program *) ptr;
	program->dinner->end_of_dinner = false;
	while (!program->dinner->end_of_dinner)
	{
		program->dinner->end_of_dinner = ft_end_of_dinner(program);
	}
	ft_stop_dinner(program);
	return (NULL);
}

void	ft_stop_dinner(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->args->num_philos)
	{
		pthread_join(program->dinner->philos[i++].thread, NULL);
		pthread_mutex_destroy(&program->dinner->philos[i].mutex_time);
		pthread_mutex_destroy(&program->dinner->forks[i]);
	}
	pthread_join(program->dinner->dispatcher, NULL);
	pthread_mutex_destroy(&program->dinner->mutex_dinner);
	pthread_mutex_destroy(&program->dinner->mutex_dead);
	pthread_mutex_destroy(&program->std_out);
	pthread_mutex_destroy(&program->mutex_time);
	pthread_mutex_destroy(&program->dinner->mutex_end);
	free (program->dinner->philos);
	free (program->dinner->forks);
	free (program->dinner);
	free (program->args);
	pthread_exit(NULL);
}
