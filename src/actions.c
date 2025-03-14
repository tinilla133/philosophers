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


static void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->dinner->forks[philo->l_fork]);
	ft_print_status(philo, picking_fork);
	pthread_mutex_lock(&philo->dinner->forks[philo->r_fork]);
	ft_print_status(philo, picking_fork);
	ft_print_status(philo, eating);
	pthread_mutex_lock(&philo->dinner->mutex_time);
	philo->last_meal_time = ft_get_current_time();
	pthread_mutex_unlock(&philo->dinner->mutex_time);
	usleep(philo->dinner->args->time_to_eat * 1000);
	pthread_mutex_lock(&philo->dinner->mutex_eating);
	philo->num_meals++;
	pthread_mutex_unlock(&philo->dinner->mutex_eating);
	pthread_mutex_unlock(&philo->dinner->forks[philo->l_fork]);
	pthread_mutex_unlock(&philo->dinner->forks[philo->r_fork]);
}

static void	ft_sleep(t_philo *philo)
{
	ft_print_status(philo, sleeping);
	usleep(philo->dinner->args->time_to_sleep * 1000);
}

static void	ft_think(t_philo *philo)
{
	ft_print_status(philo, thinking);
}

void	ft_philo_actions(t_philo *philo)
{
	ft_eat(philo);
	ft_sleep(philo);
	ft_think(philo);
}
