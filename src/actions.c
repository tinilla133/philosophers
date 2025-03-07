/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 13:43:31 by fvizcaya          #+#    #+#             */
/*   Updated: 2025/03/05 19:36:27 by fvizcaya         ###   ########.fr       */
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

void	ft_eat(t_philo *philo)
{
	ft_pickup_forks(philo);
	philo->status = eating;
	ft_print_status(philo);
	ft_wait_a_while(philo->program->args->time_to_eat);
	philo->num_meals++;
	philo->last_meal_time = ft_get_current_time();
	ft_drop_forks(philo);
}

void	ft_sleep(t_philo *philo)
{
	philo->program->dinner->action_time = ft_get_current_time();
	philo->status = sleeping;
	ft_print_status(philo);
	ft_wait_a_while(philo->program->args->time_to_sleep);
}

void	ft_think(t_philo *philo)
{
	if (philo->status != thinking)
	{
		philo->status = thinking;
		ft_print_status(philo);
	}
}
