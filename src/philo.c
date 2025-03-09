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
	(void) philo;
	/* if (!philo->id % 2)
	{
		ft_think(philo);
	} */
	while (true)
	{
		ft_think(philo);
		ft_eat(philo);
		ft_sleep(philo);
		printf("===\n");
	}
	return (NULL);
}
