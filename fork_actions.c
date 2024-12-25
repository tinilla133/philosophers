/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_actions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 16:53:22 by fvizcaya          #+#    #+#             */
/*   Updated: 2024/12/25 18:02:40 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_bool	ft_forks_free(t_dinner *dinner, t_philo *philo)
{
	int	i;
	int	r_fork_num;

	i = 0;
	if (philo->id == dinner->args.num_philos)
		r_fork_num = 0;
	else
		r_fork_num = philo->id;
	pthread_mutex_lock(&dinner->mutex_forks);
	if (dinner->forks[r_fork_num] || dinner->forks[r_fork_num - 1])
		return (false);
	pthread_mutex_unlock(&dinner->mutex_forks);
	return (true);
}

int	ft_pickup_fork(t_dinner *dinner, t_philo *philo)
{
	int	i;
	int	r_fork_num;

	i = 0;
	if (!ft_forks_free(dinner, philo))
		return (-1);
	if (philo->id == dinner->args.num_philos)
		r_fork_num = 0;
	else
		r_fork_num = philo->id;
	pthread_mutex_lock(&dinner->mutex_forks);
	philo->status = picking_fork;
	ft_print_status(philo, &dinner->std_out);
	philo->l_fork = true;
	dinner->forks[r_fork_num - 1] = true;
	philo->r_fork = true;
	dinner->forks[r_fork_num] = true;
	pthread_mutex_unlock(&dinner->mutex_forks);
	return (0);
}

void	ft_drop_forks(t_dinner *dinner, t_philo *philo)
{
	int	r_fork_num;

	if (philo->id == dinner->args.num_philos)
		r_fork_num = 0;
	else
		r_fork_num = philo->id;	
	pthread_mutex_lock(&dinner->mutex_forks);
	dinner->forks[r_fork_num - 1] = false;
	dinner->forks[r_fork_num] = false;
	philo->l_fork = false;
	philo->r_fork = false;
	pthread_mutex_unlock(&dinner->mutex_forks);
}