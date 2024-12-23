/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 13:43:31 by fvizcaya          #+#    #+#             */
/*   Updated: 2024/12/24 00:00:00 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_eat(t_philo *philo)
{
	int	aux_timer;
	int	init_timer;
	int	timer;

	if (!philo->l_fork || !philo->r_fork)
		return (-1);
	aux_timer = 0;
	init_timer = ft_get_current_time();
	timer = init_timer;
	while (aux_timer <= timer - init_timer)
		aux_timer++;
	philo->last_meal_time = ft_get_current_time();
	return (0);
}

void	ft_sleep(void)
{
	int	aux_timer;
	int	init_timer;
	int	timer;

	aux_timer = 0;
	init_timer = ft_get_current_time();
	timer = init_timer;
	while (aux_timer <= timer - init_timer)
		aux_timer++;
}

int	ft_pickup_fork(t_dinner *dinner, t_philo *philo)
{
	int	i;
	i = 0;
	pthread_mutex_lock(&dinner->mutex_forks);
	/*
	Recorremos el array de forks y, si uno está libre, lo cogemos.
	Si sólo podemos coger uno o ninguno, devolveremos -1. En otro caso 0.
	Un tenedor se coge asignando a l_fork o r_fork el valor del índice del array 
	del tenedor libre para un filósofo i.
	*/
	while (i < dinner->args.num_philos)
	{
		if (!dinner->forks[i])
		{
			if (!philo->l_fork)
			{
				philo->l_fork = i;
				dinner->forks[i] = 1;
			}
			else if (!philo->r_fork)
			{
				philo->r_fork = i;
				dinner->forks[i] = 1;
			}
		}
		i++;
	}
	pthread_mutex_unlock(&dinner->mutex_forks);
	if (philo->l_fork && philo->r_fork)
		return (0);
	return (-1);
}

void	ft_drop_forks(t_dinner *dinner, t_philo *philo)
{
	pthread_mutex_lock(&dinner->mutex_forks);
	dinner->forks[philo->l_fork] = -1;
	dinner->forks[philo->r_fork] = -1;
	philo->l_fork = 0;
	philo->r_fork = 0;
	pthread_mutex_unlock(&dinner->mutex_forks);
}
