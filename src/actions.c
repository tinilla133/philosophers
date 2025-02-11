/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 13:43:31 by fvizcaya          #+#    #+#             */
/*   Updated: 2025/02/06 21:05:49 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	ft_wait_a_while(const t_dinner *dinner, int time)
{
	int	init_timer;

	init_timer = ft_get_current_time();
	// printf("El tiempo en la función de esperar: %d\n", time);
	while (init_timer - time <= dinner->args.time_to_eat)
	{
		time = ft_get_current_time();
	}
}

int	ft_eat(t_dinner *dinner, t_philo *philo)
{
	// philo->status = eating; 
	// printf("Entra\n");
	pthread_mutex_lock(&philo->mutex_timer);
	philo->action_timer = 0;
	philo->status = eating;
	dinner->took_last_meal = philo->id;
	ft_print_status(philo, &dinner->std_out);
	ft_wait_a_while((const t_dinner *) dinner, dinner->args.time_to_eat);
	// printf("come\n");
	philo->num_meals++;
	philo->last_meal_time = ft_get_current_time();
	pthread_mutex_unlock(&philo->mutex_timer);
	pthread_mutex_unlock(&dinner->forks[philo->l_fork]);
	// printf("Soy el philo %d y acabo de soltar el tenedor izquierdo.\n", philo->id);
	pthread_mutex_unlock(&dinner->forks[philo->r_fork]);
	// printf("Soy el philo %d y acabo de coger el tenedor derecho.\n", philo->id);
	return (0);
}

void	ft_sleep(t_dinner *dinner, t_philo *philo)
{
	philo->status = sleeping;
	pthread_mutex_lock(&philo->mutex_timer);
	philo->action_timer = 0;
	ft_print_status(philo, &dinner->std_out);
	ft_wait_a_while((const t_dinner *) dinner, dinner->args.time_to_sleep);
	philo->status = thinking,
	pthread_mutex_unlock(&philo->mutex_timer);
	ft_think(dinner, philo);
}

void	ft_think(t_dinner *dinner, t_philo *philo)
{
	if (philo->status != thinking)
	{
		philo->status = thinking;
		ft_print_status(philo, &dinner->std_out);
	}
}
