/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 15:51:52 by fvizcaya          #+#    #+#             */
/*   Updated: 2025/03/19 22:38:09 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	ft_inint_args(t_args *args)
{
	args->num_philos = 0;
	args->time_to_die = 0;
	args->time_to_eat = 0;
	args->time_to_sleep = 0;
	args->times_must_eat = 0;
}

static int	ft_alloc_memory(t_dinner *dinner)
{
	int	num_philos;

	num_philos = dinner->args->num_philos;
	dinner->forks = (pthread_mutex_t *) malloc(num_philos * \
		sizeof (pthread_mutex_t));
	if (!dinner->forks)
	{
		return (-1);
	}
	dinner->philos = (t_philo *) malloc(num_philos * \
					sizeof (t_philo));
	if (!dinner->philos)
	{
		free(dinner->forks);
		return (-1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_dinner	dinner;

	dinner.args = (t_args *) malloc(sizeof (t_args));
	if (!dinner.args)
		return (-1);
	ft_inint_args(dinner.args);
	if (ft_parse_args(argc, argv, dinner.args) == -1)
	{
		printf("Arguments error.\n");
		return (0);
	}
	if (ft_alloc_memory(&dinner) == -1)
	{
		perror("Error in ft_alloc_memory");
		return (0);
	}
	ft_init(&dinner);
	ft_dinner(&dinner);
	free(dinner.forks);
	free(dinner.philos);
	free(dinner.args);
	perror("main:");
}
