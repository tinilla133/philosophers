/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 17:28:50 by fvizcaya          #+#    #+#             */
/*   Updated: 2025/03/05 21:36:49 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_philo(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *) ptr;
	pthread_mutex_lock(&philo->dinner->mutex_end);
	if (philo->dinner->end_of_dinner)
		return (pthread_mutex_unlock(&philo->dinner->mutex_end), NULL);
	pthread_mutex_unlock(&philo->dinner->mutex_end);
	pthread_mutex_lock(&philo->dinner->mutex_dead);
	if (philo->dead)
		return (pthread_mutex_unlock(&philo->dinner->mutex_dead), NULL);
	pthread_mutex_unlock(&philo->dinner->mutex_dead);
	pthread_mutex_lock(&philo->dinner->mutex_eating);
	if (philo->num_meals == philo->dinner->args->times_must_eat)
	{
		pthread_mutex_unlock(&philo->dinner->mutex_eating);
		return (NULL);
	}
	pthread_mutex_unlock(&philo->dinner->mutex_eating);
	while (true)
		ft_philo_actions(philo);
	return (NULL);
}
