/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 13:43:31 by fvizcaya          #+#    #+#             */
/*   Updated: 2025/04/01 21:54:40 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static int	ft_grab_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	if (ft_print_status(philo, picking_fork) < 0)
		return (pthread_mutex_unlock(philo->l_fork), -1);
	pthread_mutex_lock(philo->r_fork);
	if (ft_print_status(philo, picking_fork) < 0)
		return (pthread_mutex_unlock(philo->l_fork), \
			pthread_mutex_unlock(philo->r_fork), -1);
	return (0);
}

static void	ft_drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

static int	ft_eat(t_philo *philo)
{
	if (ft_grab_forks(philo) < 0)
		return (-1);
	pthread_mutex_lock(&philo->dinner->mutex_time);
	philo->last_meal_time = ft_get_current_time();
	pthread_mutex_unlock(&philo->dinner->mutex_time);
	if (ft_print_status(philo, eating) < 0)
		return (pthread_mutex_unlock(philo->l_fork), \
			pthread_mutex_unlock(philo->r_fork), -1);
	ft_usleep(philo->dinner->args->time_to_eat);
	pthread_mutex_lock(&philo->dinner->mutex_eating);
	philo->num_meals++;
	pthread_mutex_unlock(&philo->dinner->mutex_eating);
	ft_drop_forks(philo);
	return (0);
}

static int	ft_sleep(t_philo *philo)
{
	if (ft_print_status(philo, sleeping) < 0)
		return (-1);
	ft_usleep(philo->dinner->args->time_to_sleep);
	return (0);
}

int	ft_philo_actions(t_philo *philo)
{
	if (ft_eat(philo) < 0)
		return (-1);
	if (ft_sleep(philo) < 0)
		return (-1);
	if (ft_print_status(philo, thinking) < 0)
		return (-1);
	return (0);
}
