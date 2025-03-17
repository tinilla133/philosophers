/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 13:43:31 by fvizcaya          #+#    #+#             */
/*   Updated: 2025/03/17 22:43:14 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static int	ft_grab_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->dinner->forks[philo->l_fork]);
	if (ft_print_status(philo, picking_fork) < 0)
		return (pthread_mutex_unlock(&philo->dinner->forks[philo->l_fork]), -1);
	pthread_mutex_lock(&philo->dinner->forks[philo->r_fork]);
	if (ft_print_status(philo, picking_fork) < 0)
		return (pthread_mutex_unlock(&philo->dinner->forks[philo->l_fork]), \
			pthread_mutex_unlock(&philo->dinner->forks[philo->r_fork]), -1);
	if (ft_print_status(philo, eating) < 0)
		return (pthread_mutex_unlock(&philo->dinner->forks[philo->r_fork]), \
			pthread_mutex_unlock(&philo->dinner->forks[philo->r_fork]), -1);
	return (0);
}

static int	ft_drop_forks(t_philo *philo)
{
	if (philo->id % 2 && philo->dinner->args->num_philos % 2 == 0)
	{
		pthread_mutex_unlock(&philo->dinner->forks[philo->l_fork]);
		pthread_mutex_unlock(&philo->dinner->forks[philo->r_fork]);
	}
	else
	{
		pthread_mutex_unlock(&philo->dinner->forks[philo->r_fork]);
		pthread_mutex_unlock(&philo->dinner->forks[philo->l_fork]);
	}
	return (0);
}

static int	ft_eat(t_philo *philo)
{
	if (ft_grab_forks(philo) < 0)
		return (-1);
	pthread_mutex_lock(&philo->dinner->mutex_time);
	philo->last_meal_time = ft_get_current_time();
	pthread_mutex_unlock(&philo->dinner->mutex_time);
	usleep(philo->dinner->args->time_to_eat * 1000);
	pthread_mutex_lock(&philo->dinner->mutex_eating);
	philo->num_meals++;
	pthread_mutex_unlock(&philo->dinner->mutex_eating);
	if (ft_drop_forks(philo) < 0)
		return (-1);
	return (0);
}

static int	ft_sleep(t_philo *philo)
{
	if (ft_print_status(philo, sleeping) < 0)
		return (-1);
	usleep(philo->dinner->args->time_to_sleep * 1000);
	return (0);
}

int	ft_philo_actions(t_philo *philo)
{
	pthread_mutex_lock(&philo->dinner->mutex_end);
	if (philo->dinner->end_of_dinner)
		return (pthread_mutex_unlock(&philo->dinner->mutex_end), -1);
	pthread_mutex_unlock(&philo->dinner->mutex_end);
	if (ft_eat(philo) < 0)
		return (-1);
	pthread_mutex_lock(&philo->dinner->mutex_end);
	if (philo->dinner->end_of_dinner)
		return (pthread_mutex_unlock(&philo->dinner->mutex_end), -1);
	pthread_mutex_unlock(&philo->dinner->mutex_end);
	if (ft_sleep(philo) < 0)
		return (-1);
	pthread_mutex_lock(&philo->dinner->mutex_end);
	if (philo->dinner->end_of_dinner || philo->dead)
		return (pthread_mutex_unlock(&philo->dinner->mutex_end), -1);
	pthread_mutex_unlock(&philo->dinner->mutex_end);
	if (ft_print_status(philo, thinking) < 0)
		return (-1);
	return (0);
}
