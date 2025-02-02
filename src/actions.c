/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 13:43:31 by fvizcaya          #+#    #+#             */
/*   Updated: 2025/01/08 19:06:22 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	ft_eat(t_dinner *dinner, t_philo *philo)
{
	int	init_timer;

	if (!philo->l_fork || !philo->r_fork)
		return (-1);
	philo->status = eating;
	philo->action_timer = 0;
	init_timer = ft_get_current_time();
	ft_print_status(philo, &dinner->std_out);
	pthread_mutex_lock(&philo->mutex_timer);
	while (philo->action_timer - init_timer <= dinner->args.time_to_eat)
		philo->action_timer = ft_get_current_time();
	philo->num_meals++;
	philo->last_meal_time = ft_get_current_time();
	pthread_mutex_unlock(&philo->mutex_timer);
	return (0);
}

void	ft_sleep(t_dinner *dinner, t_philo *philo)
{
	int	init_timer;

	philo->status = sleeping;
	philo->action_timer = 0;
	init_timer = ft_get_current_time();
	ft_print_status(philo, &dinner->std_out);
	while (philo->action_timer - init_timer <= dinner->args.time_to_sleep)
		philo->action_timer++;
	ft_think(dinner, philo);
}

void	ft_think(t_dinner *dinner, t_philo *philo)
{
	if (philo->status != thinking)
		ft_print_status(philo, &dinner->std_out);
	philo->status = thinking;
}
