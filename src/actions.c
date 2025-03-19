/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 13:43:31 by fvizcaya          #+#    #+#             */
/*   Updated: 2025/03/19 21:18:35 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static int	ft_grab_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->dinner->forks[philo->l_fork]);
	if (ft_check_end_flag(philo->dinner) < 0)
		return (pthread_mutex_unlock(&philo->dinner->forks[philo->l_fork]), -1);
	ft_print_status(philo, picking_fork);
	pthread_mutex_lock(&philo->dinner->forks[philo->r_fork]);
	if (ft_check_end_flag(philo->dinner) < 0)
	{
		pthread_mutex_unlock(&philo->dinner->forks[philo->r_fork]);
		return (pthread_mutex_unlock(&philo->dinner->forks[philo->l_fork]), -1);
	}
	ft_print_status(philo, picking_fork);
	return (0);
}

static void	ft_drop_forks(t_philo *philo)
{
	/*
	if ((philo->id % 2) && !(philo->dinner->args->num_philos % 2))
	{
		pthread_mutex_unlock(&philo->dinner->forks[philo->l_fork]);
		pthread_mutex_unlock(&philo->dinner->forks[philo->r_fork]);
	}
	else
	{
		pthread_mutex_unlock(&philo->dinner->forks[philo->r_fork]);
		pthread_mutex_unlock(&philo->dinner->forks[philo->l_fork]);
	}
	*/
	pthread_mutex_unlock(&philo->dinner->forks[philo->l_fork]);
	pthread_mutex_unlock(&philo->dinner->forks[philo->r_fork]);
}

static int	ft_eat(t_philo *philo)
{
	if (ft_grab_forks(philo) < 0)
		return (-1);
	ft_print_status(philo, eating);
	pthread_mutex_lock(&philo->dinner->mutex_time);
	philo->last_meal_time = ft_get_current_time();
	pthread_mutex_unlock(&philo->dinner->mutex_time);
	usleep(philo->dinner->args->time_to_eat * 1000);
	pthread_mutex_lock(&philo->dinner->mutex_eating);
	philo->num_meals++;
	pthread_mutex_unlock(&philo->dinner->mutex_eating);
	ft_drop_forks(philo);
	return (0);
}

static int	ft_sleep(t_philo *philo)
{
	if (ft_check_end_flag(philo->dinner) < 0)
		return (-1);
	ft_print_status(philo, sleeping);
	usleep(philo->dinner->args->time_to_sleep * 1000);
	return (0);
}

int	ft_philo_actions(t_philo *philo)
{
	if (ft_eat(philo) < 0)
		return (-1);
	if (ft_sleep(philo) < 0)
		return (-1);
	if (ft_check_end_flag(philo->dinner) < 0)
		return (-1);
	ft_print_status(philo, thinking);
	return (0);
}
