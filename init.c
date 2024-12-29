/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 19:37:17 by fvizcaya          #+#    #+#             */
/*   Updated: 2024/12/29 22:21:24 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_alloc_data_structs(t_args args, t_dinner *dinner)
{
	dinner->forks = (int *) malloc ((args.num_philos + 1) * sizeof (int));
	if (!dinner->forks)
		return (-1);
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

	i = 0;
	while (i < dinner->num_philos)
	{
		dinner->philos[i].id = i + 1;
		dinner->philos[i].dead = false;
		dinner->philos[i].last_meal_time = ft_get_current_time();
		dinner->philos[i].l_fork = false;
		dinner->philos[i].r_fork = false;
		dinner->philos[i].num_meals = 0;
		dinner->philos[i].status = thinking;
		i++;
	}
}

static void	ft_create_threads(t_philoargs *args)
{
	int	i;

	i = 0;
	while (i < args->dinner.args.num_philos)
	{
		args->philo_num = i;
		pthread_create(&args->dinner.philos[i].thread, \
						NULL, ft_philo, args);
		i++;
	}
	pthread_create(&args->dinner.dispatcher, NULL, ft_dispatcher, \
					&args->dinner);
}

int	ft_init(t_philoargs *args)
{
	if (ft_alloc_data_structs(args->dinner.args, &args->dinner) == -1)
		return (-1);
	ft_init_forks(&args->dinner);
	ft_init_philos(&args->dinner);
	ft_create_threads(args);
	return (0);
}
