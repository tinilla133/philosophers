/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 13:43:31 by fvizcaya          #+#    #+#             */
/*   Updated: 2024/12/25 18:28:02 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_eat(t_dinner *dinner, t_philo *philo)
{
	int	aux_timer;
	int	init_timer;
	int	timer;

	if (!philo->l_fork || !philo->r_fork)
		return (-1);
	philo->status = eating;
	aux_timer = 0;
	init_timer = ft_get_current_time();
	timer = init_timer;
	ft_print_status(philo, &dinner->std_out);
	while (aux_timer <= timer - init_timer)
		aux_timer++;
	philo->num_meals++;
	philo->last_meal_time = ft_get_current_time();
	return (0);
}

void	ft_sleep(t_dinner *dinner, t_philo *philo)
{
	int	aux_timer;
	int	init_timer;
	int	timer;

	philo->status = sleeping;
	aux_timer = 0;
	init_timer = ft_get_current_time();
	timer = init_timer;
	ft_print_status(philo, &dinner->std_out);
	while (aux_timer <= timer - init_timer)
		aux_timer++;
	ft_think(dinner, philo);
}

void	ft_think(t_dinner *dinner, t_philo *philo)
{
	philo->status = thinking;
	ft_print_status(philo, &dinner->std_out);
}
