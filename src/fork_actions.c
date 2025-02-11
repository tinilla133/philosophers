/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_actions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 16:53:22 by fvizcaya          #+#    #+#             */
/*   Updated: 2025/02/06 21:05:20 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	ft_pickup_forks(t_dinner *dinner, t_philo *philo)
{
	// printf("l_fork_num ======> %d\n", philo->l_fork);
	// printf("r_fork_num ======> %d\n", philo->r_fork);
	pthread_mutex_lock(&dinner->mutex_dinner);
	if (philo->id == dinner->took_last_meal)
	{
		pthread_mutex_unlock(&dinner->mutex_dinner);
		ft_think(dinner, philo);
	}
	pthread_mutex_unlock(&dinner->mutex_dinner);
	pthread_mutex_lock(&dinner->forks[philo->l_fork]);
	philo->status = picking_fork;
	ft_print_status(philo, &dinner->std_out);
	pthread_mutex_lock(&dinner->forks[philo->r_fork]);
	ft_print_status(philo, &dinner->std_out);
	return (0);
}

void	ft_drop_forks(t_dinner *dinner, t_philo *philo)
{
	pthread_mutex_unlock(&dinner->forks[philo->l_fork]);
	pthread_mutex_unlock(&dinner->forks[philo->r_fork]);
}
