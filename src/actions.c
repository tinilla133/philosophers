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

static void	ft_wait_a_while(int a_while)
{
	int	end_time;

	end_time = ft_get_current_time() + a_while;
	// printf("El tiempo en la función de esperar: %d\n", time);
	while (ft_get_current_time() < end_time)
	{
		usleep(100);
	}
}

void	ft_eat(t_program *program)
{
	ft_pickup_forks(program);
	program->philo->status = eating;
	ft_print_status(program);
	ft_wait_a_while(program->args->time_to_eat);
	program->philo->num_meals++;
	program->philo->last_meal_time = ft_get_current_time();
	pthread_mutex_lock(&program->std_out);
    printf("El philo %d termina de comer\n", program->philo->id + 1);
    pthread_mutex_unlock(&program->std_out);
	ft_drop_forks(program);
}

void	ft_sleep(t_program *program)
{
	program->dinner->action_time = ft_get_current_time();
	program->philo->status = sleeping;
	ft_print_status(program);
	ft_wait_a_while(program->args->time_to_sleep);
}

void	ft_think(t_program *program)
{
	if (program->philo->status != thinking)
	{
		program->philo->status = thinking;
		ft_print_status(program);
	}
}
