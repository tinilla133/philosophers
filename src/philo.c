/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 17:28:50 by fvizcaya          #+#    #+#             */
/*   Updated: 2025/02/27 20:07:34 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_is_dead(t_dinner *dinner)
{
	int	i;

	i = 0;
	while (i < dinner->args.num_philos)
	{
		if (dinner->philos[i].status == dead)
			return (1);
		i++;
	}
	return (0);
}

void	*ft_philo(void *ptr)
{
	t_program	*program;

	program = (t_program *) ptr;

	pthread_mutex_lock(&program->std_out);
	printf("Hola, soy el philo %d\n", program->philo->id + 1);
	printf("He comido %d veces.\n", program->philo->num_meals);
	pthread_mutex_unlock(&program->std_out);
	pthread_mutex_lock(&program->std_out);
	printf("pa ke kieres saber eso jaja salu2\n");
	pthread_mutex_unlock(&program->std_out);
	/* if (!((program->philo->id + 1) % 2))
		ft_think(program); */
	while (true)
	{
		// ft_think(&args->dinner, &args->dinner.philos[i]);
		ft_pickup_forks(program);
		ft_eat(program);
		ft_drop_forks(program);
		ft_sleep(program);
	}
	return (NULL);
}
