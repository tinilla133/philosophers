/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 19:20:17 by fvizcaya          #+#    #+#             */
/*   Updated: 2024/12/25 20:40:34 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	ft_end_of_dinner(t_dinner *dinner)
{
	int	i;
	int	curr_time;

	i = 0;
	curr_time = ft_get_current_time();
	pthread_mutex_lock(&dinner->mutex_dispatcher);
	while (i < dinner->num_philos)
	{
		if ((curr_time - dinner->philos[i].last_meal_time) > \
			dinner->args.time_to_die)
			dinner->philos[i].dead = true;
		if (dinner->philos[i].dead)
			return (true);
		if (dinner->philos[i].num_meals == dinner->args.times_must_eat)
			return (true);
	}
	pthread_mutex_unlock(&dinner->mutex_dispatcher);
	return (false);
}

void	*ft_dispatcher(void *ptr)
{
	t_dinner 	*dinner;
	t_bool		end_of_dinner;

	dinner = (t_dinner *) ptr;
	end_of_dinner = false;
	while (!end_of_dinner)
		end_of_dinner = ft_end_of_dinner(dinner);
	return (NULL);
}

void	ft_stop_dinner(t_dinner *dinner)
{
	int	i;

	i = 0;
	while (i < dinner->args.num_philos)
		pthread_join(&dinner->philos[i++], NULL);
	free (dinner->philos);
	free (dinner->forks);
}
