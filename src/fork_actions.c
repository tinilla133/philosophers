/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_actions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 16:53:22 by fvizcaya          #+#    #+#             */
/*   Updated: 2025/03/05 19:31:17 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	ft_pickup_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->program->dinner->forks[philo->l_fork]);
	philo->status = picking_fork;
	ft_print_status(philo, picking_fork);
	pthread_mutex_lock(&philo->program->dinner->forks[philo->r_fork]);
	philo->status = picking_fork;
	ft_print_status(philo, picking_fork);
}

void	ft_drop_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->program->std_out);
	printf("Entra en ft_drop_forks el philo %d\n", philo->id + 1);
	pthread_mutex_unlock(&philo->program->std_out);
	pthread_mutex_unlock(&philo->program->dinner->forks[philo->l_fork]);
	pthread_mutex_unlock(&philo->program->dinner->forks[philo->r_fork]);
}
