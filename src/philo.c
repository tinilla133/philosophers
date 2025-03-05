/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 17:28:50 by fvizcaya          #+#    #+#             */
/*   Updated: 2025/03/05 21:36:49 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_philo(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *) ptr;
	/* pthread_mutex_lock(&program->std_out);
	printf("Hola, soy el philo %d\n", program->philo->id + 1);
	printf("He comido %d veces.\n", program->philo->num_meals);
	pthread_mutex_unlock(&program->std_out); */
	pthread_mutex_lock(&philo->program->std_out);
	// printf("Dirección del philo %d: %p\n", program->philo->id + 1, program->philo);
	pthread_mutex_unlock(&philo->program->std_out);
	if (!philo->id % 2)
	{
		ft_think(philo);
		usleep(10000);
	}
	// usleep(1000);
	while (true)
	{
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
	return (NULL);
}
