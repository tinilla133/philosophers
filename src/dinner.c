/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 19:20:17 by fvizcaya          #+#    #+#             */
/*   Updated: 2025/02/27 20:00:12 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	ft_end_of_dinner(t_dinner *dinner)
{
	int		i;
	int		curr_time;
	t_bool	ret;

	i = 0;
	ret = false;
	while (i < dinner->args.num_philos)
	{
		curr_time = ft_get_current_time();
		pthread_mutex_lock(&dinner->std_out);
		printf("Tiempo sin comer del philo %d: %d\n", i + 1, curr_time - dinner->philos[i].last_meal_time);
		pthread_mutex_unlock(&dinner->std_out);
		pthread_mutex_lock(&dinner->mutex_dispatcher);
		if ((curr_time - dinner->philos[i].last_meal_time) > \
			dinner->args.time_to_die)
		{
			dinner->philos[i].status = dead;
			ret = true;
		}
		if (dinner->philos[i].num_meals == dinner->args.times_must_eat)
			ret = true;
		pthread_mutex_unlock(&dinner->mutex_dispatcher);
		i++;
	}
	return (ret);
}

void	*ft_dispatcher(void *ptr)
{
	t_program	*program;

	program = (t_program *) ptr;
	pthread_mutex_lock(&program->dinner->mutex_dispatcher);
	while (!program->dinner->end_of_dinner)
	{
		pthread_mutex_lock(&program->dinner->std_out);
		printf("====> Hilo dispatcher <====\n");
		printf("end_of_dinner =====> %d\n", program->dinner->end_of_dinner);
		pthread_mutex_unlock(&program->dinner->std_out);
		program->dinner->end_of_dinner = ft_end_of_dinner(program->dinner);
	}
	pthread_mutex_unlock(&program->dinner->mutex_dispatcher);
	ft_stop_dinner(program);
	return (NULL);
}

void	ft_stop_dinner(t_program *program)
{
	int	i;

	pthread_mutex_lock(&program->dinner->std_out);
	printf("========> Entramos en ft_stop_dinner()\n");
	pthread_mutex_unlock(&program->dinner->std_out);

	i = 0;
	while (i < program->args->num_philos)
	{
		pthread_mutex_destroy(&program->dinner->forks[i]);
		pthread_join(program->dinner->philos[i++].thread, NULL);
	}
	pthread_mutex_destroy(&program->dinner->mutex_dinner);
	pthread_mutex_destroy(&program->dinner->mutex_dispatcher);
	pthread_exit(NULL);
	free (program->dinner->philos);
	free (program->dinner->forks);
}
