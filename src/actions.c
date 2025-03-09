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

/* static void	ft_wait_a_while(int a_while)
{
	int	end_time;

	while
	end_time = ft_get_current_time() + a_while;
	while (ft_get_current_time() < end_time)
	{
		// usleep(1000);
	}
	
}
*/

void	ft_eat(t_philo *philo)
{
	// ft_pickup_forks(philo);
	pthread_mutex_lock(&philo->program->dinner->forks[philo->l_fork]);
	philo->status = picking_fork;
	ft_print_status(philo, picking_fork);
	pthread_mutex_lock(&philo->program->dinner->forks[philo->r_fork]);
	philo->status = picking_fork;
	ft_print_status(philo, picking_fork);
	philo->status = eating;
	ft_print_status(philo, eating);
	usleep(philo->program->args->time_to_eat * 1000);
	//ft_wait_a_while(philo->program->args->time_to_eat);
	pthread_mutex_lock(&philo->mutex_time);
	philo->num_meals++;
	philo->last_meal_time = ft_get_current_time();
	pthread_mutex_unlock(&philo->mutex_time);
	pthread_mutex_unlock(&philo->program->dinner->forks[philo->l_fork]);
	pthread_mutex_unlock(&philo->program->dinner->forks[philo->r_fork]);
	pthread_mutex_lock(&philo->program->std_out);
	printf("Ha soltado los tenedores el philo %d\n", philo->id + 1);
	pthread_mutex_unlock(&philo->program->std_out);
	// ft_drop_forks(philo);
}

void	ft_sleep(t_philo *philo)
{
	// philo->program->dinner->action_time = ft_get_current_time();
	philo->status = sleeping;
	pthread_mutex_lock(&philo->program->std_out);
	ft_print_status(philo, sleeping);
	pthread_mutex_unlock(&philo->program->std_out);
	usleep(philo->program->args->time_to_sleep * 1000);
	// ft_wait_a_while(philo->program->args->time_to_sleep);
}

void	ft_think(t_philo *philo)
{
	if (philo->status != thinking)
	{
		philo->status = thinking;
		ft_print_status(philo, thinking);
	}
}
