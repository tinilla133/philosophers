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

	if (!(program->philo->id % 2))
	{
		program->philo->r_fork = (program->philo->id + 1) % program->args->num_philos;
		program->philo->l_fork = program->philo->id;
	}
	else
	{
		program->philo->l_fork = (program->philo->id + 1) % program->args->num_philos;
		program->philo->r_fork = program->philo->id;
	}
    if (program->philo->id == program->args->num_philos - 1)
    {
        fork_swap = program->philo->l_fork;
        program->philo->l_fork = program->philo->r_fork;
        program->philo->r_fork = fork_swap;
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
		program->dinner->philos[i].status = thinking;
        program->philo = &program->dinner->philos[i];
		ft_get_fork_number(program);
		i++;
	}
}

static int	ft_create_threads(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->args->num_philos)
	{
		program->philo = &program->dinner->philos[i];
		printf("Se va a crear el hilo del philo %d\n", program->philo->id);
		if (pthread_create(&program->dinner->philos[i].thread, \
						NULL, ft_philo, program) != 0)
			return (-1);
		i++;
	}
    if (pthread_create(&program->dinner->dispatcher, NULL, ft_dispatcher, \
		  &program->dinner) != 0)
		return (-1);
	return (0);
}

int	ft_init(t_program *program)
{
	int i;

	i = 0;
	if (ft_alloc_data_structs(program) == -1)
		return (-1);
	// program->args->dinner->took_last_meal = args->philo_num;
	program->dinner->end_of_dinner = false;
	ft_init_philos(program);
    while (i < program->args->num_philos)
		if (pthread_mutex_init(&program->dinner->forks[i++], NULL) != 0)
			return (-1);
	if (pthread_mutex_init(&program->dinner->mutex_dispatcher, NULL) != 0 || \
		pthread_mutex_init(&program->std_out, NULL) != 0)
		return (-1);
	ft_create_threads(program);
	return (0);
}