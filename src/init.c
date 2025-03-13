/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 19:37:17 by fvizcaya          #+#    #+#             */
/*   Updated: 2025/03/13 20:35:29 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_alloc_data_structs(t_program *program)
{
	program->dinner->forks = (pthread_mutex_t *) malloc (program->args->num_philos * \
		sizeof (pthread_mutex_t));
	if (!program->dinner->forks)
		return (-1);
	program->dinner->philos = (t_philo *) malloc (program->args->num_philos * \
					sizeof (t_philo));
	if (!program->dinner->philos)
		return (-1);
	return (0);
}

static void	ft_get_fork_number(t_program *program)
{
    int fork_swap;
	int i;

	(void) fork_swap;
	/* if (!(program->philo->id % 2))
	{
		program->philo->r_fork = (program->philo->id + 1) % program->args->num_philos;
		program->philo->l_fork = program->philo->id;
	}
	else
	{
		program->philo->r_fork = program->philo->id;
		program->philo->l_fork = (program->philo->id + 1) % program->args->num_philos;
	}
	*/
	/*
	program->philo->l_fork = program->philo->id;
	program->philo->r_fork = (program->philo->id + 1) % program->args->num_philos;
	if (program->philo->id == program->args->num_philos - 1)
	{
		fork_swap = program->philo->l_fork;
		program->philo->l_fork = program->philo->r_fork;
		program->philo->r_fork = fork_swap;
	}
	*/
	i = 0;
	printf("El número de filósofos es %d\n", program->args->num_philos);
	while (i < program->args->num_philos)
	{
		if (!(program->dinner->philos[i].id % 2))
		{
			program->dinner->philos[i].r_fork = (program->dinner->philos[i].id + 1) % program->args->num_philos;
			program->dinner->philos[i].l_fork = program->dinner->philos[i].id;
		}
		else
		{
			program->dinner->philos[i].r_fork = program->dinner->philos[i].id;
			program->dinner->philos[i].l_fork = (program->dinner->philos[i].id + 1) % program->args->num_philos;
		}
		i++;
	}
	i = 0;
	while (i < program->args->num_philos)
	{
		printf("El philo %d tiene asignados los tenedores %d y %d\n", program->dinner->philos[i].id + 1, \
		program->dinner->philos[i].l_fork + 1, program->dinner->philos[i].r_fork + 1);
		i++;
	}
}

static void	ft_init_philos(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->args->num_philos)
	{
		program->dinner->philos[i].id = i;
		program->dinner->philos[i].dead = false;
		program->dinner->philos[i].last_meal_time = ft_get_current_time();
		program->dinner->philos[i].num_meals = 0;
		program->dinner->philos[i].program = program;
		ft_get_fork_number(program);
		i++;
	}
}

static int	ft_create_threads(t_program *program)
{
	int	i;

	i = 0;/* 
	pthread_mutex_lock(&program->std_out);
	pthread_mutex_unlock(&program->std_out); */
	printf("Numero de hilos creados: %d\n", program->args->num_philos);
	while (i < program->args->num_philos)
	{
		printf("philo : %d, creating...\n", program->dinner->philos[i].id);
		if (pthread_create(&program->dinner->philos[i].thread, \
						NULL, ft_philo, &program->dinner->philos[i]) != 0)
			return (-1);
		i++;
	}
	printf("Ha pasado de crear el hilo dispatcher\n");
/* 	if (pthread_create(&program->dinner->dispatcher, NULL, ft_dinner, \
		program) != 0)
	{
		pthread_mutex_lock(&program->std_out);
		printf("Error creating dispatcher thread\n");
		pthread_mutex_unlock(&program->std_out);
		return (-1);
	} */
	return (0);
}

int	ft_init(t_program *program)
{
	int i;

	i = 0;
	if (ft_alloc_data_structs(program) == -1)
		return (perror("ERROR"), -1);
	program->dinner->end_of_dinner = false;
	ft_init_philos(program);
    while (i < program->args->num_philos)
		if (pthread_mutex_init(&program->dinner->forks[i++], NULL) != 0)
			return (-1);
	if (pthread_mutex_init(&program->dinner->mutex_dinner, NULL) != 0 || \
		pthread_mutex_init(&program->std_out, NULL) != 0 )
		return (-1);
	if (ft_create_threads(program) != 0)
		return (-1); 
	return (0);
}
