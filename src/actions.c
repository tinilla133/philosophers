/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 13:43:31 by fvizcaya          #+#    #+#             */
/*   Updated: 2025/02/27 20:05:13 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	ft_wait_a_while(const t_args *args, int time)
{
	int	init_timer;

	init_timer = ft_get_current_time();
	// printf("El tiempo en la función de esperar: %d\n", time);
	while (init_timer - time <= args->time_to_eat)
	{
		time = ft_get_current_time();
	}
}

int	ft_eat(t_program *program)
{
	pthread_mutex_lock(&program->philo->mutex_timer);
	program->philo->action_timer = 0;
	program->philo->status = eating;
	program->dinner->took_last_meal = program->philo->id;
	ft_print_status(program);
	ft_wait_a_while((const t_args *) program->args, program->args->time_to_eat);
	program->philo->num_meals++;
	program->philo->last_meal_time = ft_get_current_time();
	pthread_mutex_unlock(&program->philo->mutex_timer);
	return (0);
}

void	ft_sleep(t_program *program)
{
	program->philo->status = sleeping;
	pthread_mutex_lock(&program->philo->mutex_timer);
	program->philo->action_timer = 0;
	ft_print_status(program);
	ft_wait_a_while((const t_args *) program->args, \
					program->args->time_to_sleep);
	pthread_mutex_unlock(&program->philo->mutex_timer);
	ft_think(program);
}

void	ft_think(t_program *program)
{
	if (program->philo->status != thinking)
	{
		program->philo->status = thinking;
		ft_print_status(program);
	}
}
