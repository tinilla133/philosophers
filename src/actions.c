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

/* static void	ft_wait_a_while(const t_args *args, int time)
{
	int	end_timer;

	(void) args;
	end_timer = ft_get_current_time() + time;
	// printf("El tiempo en la función de esperar: %d\n", time);
	while (ft_get_current_time() < end_timer)
	{
		usleep(100);
	}
}
	*/

void	ft_eat(t_program *program)
{
	program->philo->action_timer = ft_get_current_time();
	program->philo->status = eating;
	ft_print_status(program);
	// pthread_mutex_lock(&program->dinner->mutex_counter);
	pthread_mutex_lock(&program->std_out);
	while (ft_get_current_time() - program->philo->action_timer < \
			program->args->time_to_eat)
	{
		printf("El philo %d entra en el while de ft_eat\n", program->philo->id + 1);
		printf("Tiempo de comer %d\n", program->args->time_to_eat);
		printf("El philo %d está comiendo %d ms\n", program->philo->id + 1, ft_get_current_time() - program->philo->action_timer);
		usleep(1000);
	}
	pthread_mutex_unlock(&program->std_out);
	// pthread_mutex_unlock(&program->dinner->mutex_counter);
	// ft_wait_a_while((const t_args *) program->args, program->args->time_to_eat);
	program->philo->num_meals++;
	program->philo->last_meal_time = ft_get_current_time();

	pthread_mutex_lock(&program->std_out);
    printf("El philo %d termina de comer\n", program->philo->id + 1);
    pthread_mutex_unlock(&program->std_out);
}

void	ft_sleep(t_program *program)
{
	program->philo->action_timer = ft_get_current_time();
	program->philo->status = sleeping;
	ft_print_status(program);
	while (ft_get_current_time() < program->philo->action_timer + \
			program->args->time_to_sleep)
	{
		usleep(100);
	}
}

void	ft_think(t_program *program)
{
	if (program->philo->status != thinking)
	{
		program->philo->status = thinking;
		ft_print_status(program);
	}
}
