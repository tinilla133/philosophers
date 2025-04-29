/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 17:28:50 by fvizcaya          #+#    #+#             */
/*   Updated: 2025/04/01 21:31:50 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_single_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	ft_print_status(philo, picking_fork);
	pthread_mutex_unlock(philo->l_fork);
	ft_usleep(philo->dinner->args->time_to_die);
}

void	*ft_philo(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *) ptr;
	if (philo->dinner->args->num_philos == 1)
		return (ft_single_philo(philo), NULL);
	if (philo->id % 2 != 0)
		if (ft_print_status(philo, thinking) < 0)
			return (NULL);
	pthread_mutex_lock(&philo->dinner->mutex_time);
	philo->last_meal_time = ft_get_current_time();
	pthread_mutex_unlock(&philo->dinner->mutex_time);
	while (true)
	{
		if (ft_check_end(philo->dinner) < 0)
			return (NULL);
		pthread_mutex_lock(&philo->dinner->mutex_eating);
		pthread_mutex_unlock(&philo->dinner->mutex_eating);
		if (ft_philo_actions(philo) < 0)
			return (NULL);
	}
	return (NULL);
}
