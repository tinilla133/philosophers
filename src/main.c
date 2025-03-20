/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 15:51:52 by fvizcaya          #+#    #+#             */
/*   Updated: 2025/03/21 00:54:58 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	ft_inint_pointers(void *ptr)
{
	t_dinner	*dinner;

	dinner = (t_dinner *) ptr;
	dinner->args = NULL;
	dinner->philos = NULL;
	dinner->forks = NULL;
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

static void	ft_free_memory(void *ptr)
{
	t_dinner	*dinner;

	dinner = (t_dinner *) ptr;
	free(dinner->forks);
	free(dinner->philos);
	free(dinner->args);
	dinner->forks = NULL;
	dinner->philos = NULL;
	dinner->args = NULL;
}

int	main(int argc, char **argv)
{
	t_dinner	dinner;

	ft_inint_pointers(&dinner);
	dinner.args = (t_args *) malloc(sizeof (t_args));
	if (!dinner.args)
		return (-1);
	if (ft_parse_args(argc, argv, dinner.args) == -1)
	{
		ft_free_memory(&dinner);
		printf("Arguments error.\n");
		return (0);
	}
	if (ft_alloc_memory(&dinner) == -1)
	{
		ft_free_memory(&dinner);
		printf("Error allocation memory.\n");
		return (0);
	}
	ft_init(&dinner);
	ft_dinner(&dinner);
	ft_free_memory(&dinner);
}
