/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 19:37:17 by fvizcaya          #+#    #+#             */
/*   Updated: 2024/12/25 00:49:30 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_alloc_data_structs(t_args args, t_dinner *dinner)
{
	dinner->forks = (int *) malloc (args.num_philos * sizeof (int));
	if (!dinner->forks)
		return (-1);
	ft_init_forks(dinner);
	dinner->philos = (t_philo *) malloc ((args.num_philos + 1) * \
					sizeof (t_philo));
	if (!dinner->philos)
		return (-1);
	return (0);
}

static void	ft_init_forks(t_dinner *dinner)
{
	int	i;

	i = 0;
	while (i < (dinner->num_philos - 1))
		dinner->forks[i++] = 0;
}

static void	ft_init_philos(t_dinner *dinner)
{
	int	i;

	i = INITIAL_PHILOSOPHER;
	while (i < dinner->num_philos)
	{
		dinner->philos[i].id = i;
		dinner->philos[i].dead = 0;
		dinner->philos[i].last_meal_time = ft_get_current_time();
		dinner->philos[i].l_fork = -1;
		dinner->philos[i].r_fork = -1;
		dinner->philos[i].times_eaten = 0;
		dinner->philos[i].status = thinking;
		i++;
	}
	return (0);
}

int	ft_init(t_dinner *dinner)
{
	if (ft_alloc_data_structs(dinner->args, dinner) == -1)
		return (-1);
	ft_init_forks(dinner);
	ft_init_philos(dinner);
	return (0);
}