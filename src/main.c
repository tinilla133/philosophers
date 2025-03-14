/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 15:51:52 by fvizcaya          #+#    #+#             */
/*   Updated: 2025/03/05 21:48:11 by fvizcaya         ###   ########.fr       */
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

static int	ft_alloc_dinner(t_dinner *dinner)
{
	dinner->args = (t_args *) malloc(sizeof (t_args));
	if (!dinner->args)
		return (-1);
	dinner = (t_dinner *) malloc (sizeof (t_dinner));
	if (!dinner)
	{
		free (dinner->args);
		return (-1);
	}
	return (0);
}

static int	ft_alloc_philos_and_forks(t_dinner *dinner)
{
	int	num_philos;

	num_philos = dinner->args->num_philos;
	dinner->forks = (pthread_mutex_t *) malloc(num_philos * \
		sizeof (pthread_mutex_t));
	if (!dinner->forks)
		return (-1);
	dinner->philos = (t_philo *) malloc(num_philos * \
					sizeof (t_philo));
	if (!dinner->philos)
		return (-1);
	return (0);
}

static void	ft_print_arguments(const t_args *args)
{
	printf("Num philos: %d\n", args->num_philos);
	printf("Time to eat: %d\n", args->time_to_eat);
	printf("Time to sleep: %d\n", args->time_to_sleep);
	printf("Time to die: %d\n", args->time_to_die);
	printf("Time must eat: %d\n", args->times_must_eat);
}
int	main(int argc, char **argv)
{
	t_dinner	dinner;

	if (ft_alloc_dinner(&dinner) == -1)
	{
		perror("Error in ft_alloc_program");
		return (0);
	}
	ft_inint_args(dinner.args);
	if (ft_parse_args(argc, argv, dinner.args) == -1)
	{
		printf("Arguments error.\n");
		return (0);
	}
	ft_print_arguments(dinner.args);
	if (ft_alloc_philos_and_forks(&dinner) == -1)
	{
		perror("Error in ft_alloc_philos_and_forks");
		return (0);
		// Liberar memoria de program antes de salir
	}
	ft_init(&dinner);
	ft_dinner(&dinner);
}
