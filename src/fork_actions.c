/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_actions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya42 <fvizcaya42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 16:53:22 by fvizcaya          #+#    #+#             */
/*   Updated: 2025/02/24 19:10:40 by fvizcaya42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	ft_pickup_forks(t_program *program)
{
	pthread_mutex_lock(&program->std_out);
	printf("Entra en ft_pickup_forks el philo %d\n", program->philo->id + 1);
	pthread_mutex_unlock(&program->std_out);
	pthread_mutex_lock(&program->dinner->forks[program->philo->l_fork]);
	program->philo->status = picking_fork;
	ft_print_status(program);
	pthread_mutex_lock(&program->dinner->forks[program->philo->r_fork]);
	ft_print_status(program);
	return (0);
}

void	ft_drop_forks(t_program *program)
{
	pthread_mutex_unlock(&program->dinner->forks[program->philo->l_fork]);
	pthread_mutex_unlock(&program->dinner->forks[program->philo->r_fork]);
}
