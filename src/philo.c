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

	usleep(1000);
	if (!((program->philo->id + 1) % 2))
		ft_think(program->dinner, program->philo);
	while (true)
	{
		// printf("¡Hola!, soy el philo %d\n", i);
		// ft_think(&args->dinner, &args->dinner.philos[i]);
		ft_pickup_forks(program->dinner, program->philo);
		ft_eat(program->dinner, program->philo);
		ft_drop_forks(program->dinner, program->philo);
		ft_sleep(program->dinner, program->philo);
	}
	return (NULL);
}
