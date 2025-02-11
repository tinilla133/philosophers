/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 19:37:17 by fvizcaya          #+#    #+#             */
/*   Updated: 2025/02/06 21:19:28 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_alloc_data_structs(t_args args, t_dinner *dinner)
{
	dinner->forks = (pthread_mutex_t *) malloc ((args.num_philos) * \
		sizeof (pthread_mutex_t));
	if (!dinner->forks)
		return (-1);
	dinner->philos = (t_philo *) malloc ((args.num_philos) * \
					sizeof (t_philo));
	if (!dinner->philos)
		return (-1);
	return (0);
}

static void	ft_init_forks(t_dinner *dinner)
{
	int	i;

	i = 0;
	while (i < (dinner->args.num_philos - 1))
		pthread_mutex_init(&dinner->forks[i++], NULL);
}

static void	ft_get_fork_number(const t_dinner *dinner, t_philo *philo)
{
	if (!(philo->id % 2))
	{
		philo->r_fork = (philo->id + 1) % dinner->args.num_philos;
		philo->l_fork = philo->id;
	}
	else
	{
		philo->l_fork = (philo->id + 1) % dinner->args.num_philos;
		philo->r_fork = philo->id;
	}
}


static void	ft_init_philos(t_dinner *dinner)
{
	int	i;

	i = 0;
	while (i < dinner->args.num_philos)
	{
		dinner->philos[i].id = i;
		dinner->philos[i].dead = false;
		dinner->philos[i].last_meal_time = ft_get_current_time();
		dinner->philos[i].num_meals = 0;
		// dinner->philos[i].status = thinking;
		ft_get_fork_number((const t_dinner *) dinner, &dinner->philos[i]);
		i++;
	}
}

static void	ft_create_threads(t_philoargs *args)
{
	int	i;

	pthread_create(&args->dinner.dispatcher, NULL, ft_dispatcher, \
					&args->dinner);
	i = 0;
	while (i < args->dinner.args.num_philos)
	{
		printf("Num philos: %d\n", args->dinner.args.num_philos);
		args->philo_num = i;
		pthread_create(&args->dinner.philos[i].thread, \
						NULL, ft_philo, args);
		i++;
	}
	printf("Retornamos de ft_create_threads()\n");
}

int	ft_init(t_philoargs *args)
{
	if (ft_alloc_data_structs(args->dinner.args, &args->dinner) == -1)
		return (-1);
	args->dinner.took_last_meal = args->philo_num;
	ft_init_forks(&args->dinner);
	ft_init_philos(&args->dinner);
	pthread_mutex_init(&args->dinner.mutex_dinner, NULL);
	pthread_mutex_init(&args->dinner.mutex_dispatcher, NULL);
	ft_create_threads(args);
	return (0);
}
