/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 19:37:17 by fvizcaya          #+#    #+#             */
/*   Updated: 2025/02/27 19:40:39 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_get_fork_number(t_program *program, int philo_id)
{
    int fork_swap;
	int	num_philos;

	num_philos = program->args->num_philos;
	if (!(philo_id % 2))
	{
		program->dinner->philos[philo_id].r_fork = (philo_id + 1) % num_philos;
		program->dinner->philos[philo_id].l_fork = philo_id;
	}
	else
	{
		program->dinner->philos[philo_id].r_fork = philo_id;
		program->dinner->philos[philo_id].l_fork = (philo_id + 1) % num_philos;
	}
	if (philo_id == program->args->num_philos - 1)
	{
		fork_swap = program->dinner->philos[philo_id].r_fork;
		program->dinner->philos[philo_id].r_fork = \
			program->dinner->philos[philo_id].l_fork;
		program->dinner->philos[philo_id].l_fork = fork_swap;
	}
	printf("El philo %d tiene asignados los tenedores %d y %d\n", philo_id + 1, \
			program->dinner->philos[philo_id].l_fork + 1, program->dinner->philos[philo_id].r_fork + 1);
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
		program->dinner->philos[i].status = thinking;
		program->dinner->philos[i].program = program;
		ft_get_fork_number(program, i);
		i++;
	}
}

static int	ft_create_threads(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->args->num_philos)
	{
		if (pthread_create(&program->dinner->philos[i].thread, \
						NULL, ft_philo, &program->dinner->philos[i]) != 0)
			return (-1);
		i++;
	}
	if (pthread_create(&program->dinner->dispatcher, NULL, ft_dinner, \
		&program) != 0)
		return (-1);
	return (0);
}

static int	ft_init_mutexes(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->args->num_philos)
		if (pthread_mutex_init(&program->dinner->forks[i++], NULL) != 0 || \
			pthread_mutex_init(&program->dinner->philos[i - 1].mutex_time, NULL) != 0)
			return (-1);
	if ((pthread_mutex_init(&program->dinner->mutex_dinner, NULL) != 0) || \
		(pthread_mutex_init(&program->dinner->mutex_dead, NULL) != 0) || \
		(pthread_mutex_init(&program->std_out, NULL) != 0) || \
		(pthread_mutex_init(&program->debug, NULL) != 0) || \
		(pthread_mutex_init(&program->mutex_time, NULL) != 0) || \
		(pthread_mutex_init(&program->dinner->mutex_end, NULL) != 0))
		return (-1);
	return (0);
}

int	ft_init(t_program *program)
{
	program->dinner->end_of_dinner = false;
	ft_init_philos(program);
	if (ft_init_mutexes(program) != 0)
	{
		perror("Error: ft_init_mutexes");
		return (-1);
	}
	if (ft_create_threads(program) != 0)
	{
		perror("Error: ft_create_threads");
		return (-1);
	}
	return (0);
}
