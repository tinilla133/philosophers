/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_actions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 16:53:22 by fvizcaya          #+#    #+#             */
/*   Updated: 2024/12/25 14:36:09 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_forks_free(t_dinner *dinner)
{
	int	i;
	int	free_forks;

	i = 0;
	free_forks = 0;
	while ((i < dinner->args.num_philos) || (free_forks < 2))
	{
		if (!dinner->forks[i])
			free_forks++;
		i++;
	}
	if (free_forks >= 2)
		return (1);
	return (0);
}

int	ft_pickup_fork(t_dinner *dinner, t_philo *philo)
{
	int	i;
	int	r_fork_num;

	i = 0;
	if (!ft_forks_free(dinner))
		return (-1);
	pthread_mutex_lock(&dinner->mutex_forks);
	philo->status = picking_fork;
	ft_print_status(philo, &dinner->std_out);
	
	while (i < dinner->args.num_philos || !(philo->l_fork && philo->r_fork))
	{
		if (!dinner->forks[i])
		{
			if (!philo->l_fork)
				philo->l_fork = i;
			else if (!philo->r_fork)
				philo->r_fork = i;
			dinner->forks[i] = 1;
		}
		i++;
	}
	pthread_mutex_unlock(&dinner->mutex_forks);
	return (0);
}

void	ft_drop_forks(t_dinner *dinner, t_philo *philo)
{
	pthread_mutex_lock(&dinner->mutex_forks);
	dinner->forks[philo->l_fork] = -1;
	dinner->forks[philo->r_fork] = -1;
	philo->l_fork = -1;
	philo->r_fork = -1;
	pthread_mutex_unlock(&dinner->mutex_forks);
}