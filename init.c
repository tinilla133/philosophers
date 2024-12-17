/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 19:37:17 by fvizcaya          #+#    #+#             */
/*   Updated: 2024/08/28 19:57:46 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_init_values(t_args args, t_dinning_r *dinning_r)
{
	dinning_r->forks = (int *) malloc (args.num_philos * sizeof (int));
	if (!dinning_r->forks)
		return (-1);
	ft_init_forks(dinning_r->forks, args.num_philos);
	dinning_r->philos = (t_philo *) malloc (args.num_philos * sizeof (t_philo));
	if (!dinning_r->philos)
		return (-1);
	ft_init_philos(dinning_r->philos, args.num_philos);
	dinning_r->m_forks = (pthread_mutex_t **) malloc (args.num_philos * sizeof (t_philo *));
	if (!dinning_r->m_forks)
		return (-1);
}

int	ft_init_forks(int *forks, int size)
{
	int	i;

	i = 0;
	while (i < size)
		forks[i++] = 0;
}

int	ft_init_philos(t_philo *philos, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		philos[i].id = i;
		philos[i].dead = 0;
		philos[i].last_time_eaten = 0;
		philos[i].l_fork = -1;
		philos[i].r_fork = -1;
		philos[i].times_eaten = 0;
		philos[i].status = 0;
		i++;
	}
	return (0);
}

