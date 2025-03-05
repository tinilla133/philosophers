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

	i = 0;
	curr_time = ft_get_current_time();
	while (i < program->args->num_philos)
	{
		pthread_mutex_lock(&program->std_out);
		printf("Tiempo sin comer del philo %d: %d\n", i + 1, curr_time - program->dinner->philos[i].last_meal_time);
		pthread_mutex_unlock(&program->std_out);
		pthread_mutex_lock(&program->dinner->mutex_dinner);
		if ((curr_time - program->dinner->philos[i].last_meal_time) > \
			program->args->time_to_die)
		{
			program->dinner->philos[i].status = dead;
			pthread_mutex_unlock(&program->dinner->mutex_dinner);
			return (true);
		}
		pthread_mutex_unlock(&program->dinner->mutex_dinner);
		i++;
	}
	return (false);
}

static t_bool	ft_num_meals_reached(t_program *program)
{
	int		i;

	if (program->args->times_must_eat == -1)
		return (false);
	i = 0;
	while (i < program->args->num_philos)
	{
		pthread_mutex_lock(&program->dinner->mutex_dinner);
		if (program->dinner->philos[i].num_meals < program->args->times_must_eat)
		{
			pthread_mutex_unlock(&program->dinner->mutex_dinner);
			return (false);
		}
		pthread_mutex_unlock(&program->dinner->mutex_dinner);
		i++;
	}
	return (true);
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
	pthread_mutex_lock(&program->std_out);
	printf("========> Entramos en ft_dinner()\n");
	pthread_mutex_unlock(&program->std_out);
	while (!program->dinner->end_of_dinner)
	{
		pthread_mutex_lock(&program->std_out);
		printf("====> Hilo dinner <====\n");
		printf("end_of_dinner =====> %d\n", program->dinner->end_of_dinner);
		pthread_mutex_unlock(&program->std_out);
		program->dinner->end_of_dinner = ft_end_of_dinner(program);
	}
	ft_stop_dinner(program);
	return (NULL);
}

void	ft_stop_dinner(t_program *program)
{
	int	i;

	pthread_mutex_lock(&program->std_out);
	printf("========> Entramos en ft_stop_dinner()\n");
	pthread_mutex_unlock(&program->std_out);

	i = 0;
	while (i < program->args->num_philos)
	{
		pthread_join(program->dinner->philos[i++].thread, NULL);
		pthread_mutex_destroy(&program->dinner->forks[i]);
	}
	pthread_join(program->dinner->dispatcher, NULL);
	pthread_mutex_destroy(&program->dinner->mutex_dinner);
	pthread_mutex_destroy(&program->std_out);
	free (program->dinner->philos);
	free (program->dinner->forks);
	pthread_exit(NULL);
}
