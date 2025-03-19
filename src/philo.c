/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 17:28:50 by fvizcaya          #+#    #+#             */
/*   Updated: 2025/03/19 20:32:49 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_philo(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *) ptr;
	philo->last_meal_time = ft_get_current_time();
	while (true)
	{
		if (ft_check_end_flag(philo->dinner) < 0)
			return (NULL);
		pthread_mutex_lock(&philo->dinner->mutex_eating);
		if (philo->num_meals == philo->dinner->args->times_must_eat)
		{
			pthread_mutex_unlock(&philo->dinner->mutex_eating);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->dinner->mutex_eating);
		if (ft_philo_actions(philo) < 0)
			return (NULL);
	}
	return (NULL);
}
