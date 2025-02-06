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
	pthread_mutex_lock(&dinner->forks[philo->l_fork]);
	philo->status = picking_fork;
	ft_print_status(philo, &dinner->std_out);
	printf("Soy el philo %d y acabo de coger el tenedor izquierdo.\n", philo->id);
	pthread_mutex_lock(&dinner->forks[philo->r_fork]);
	ft_print_status(philo, &dinner->std_out);
	printf("Soy el philo %d y acabo de coger el tenedor derecho.\n", philo->id);
	return (0);
}

// void	ft_drop_forks(t_dinner *dinner, t_philo *philo)
// {
// 	pthread_mutex_unlock(&dinner->forks[philo->l_fork]);
// 	printf("Soy el philo %d y acabo de soltar el tenedor izquierdo.\n", philo->id);
// 	pthread_mutex_unlock(&dinner->forks[philo->r_fork]);
// 	printf("Soy el philo %d y acabo de coger el tenedor derecho.\n", philo->id);

// }
