/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 14:41:58 by fvizcaya          #+#    #+#             */
/*   Updated: 2025/03/30 20:01:23 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

inline time_t	ft_get_current_time(void)
{
	struct timeval	curr_time;

	gettimeofday(&curr_time, NULL);
	return ((curr_time.tv_sec * (time_t) 1000 + \
			(curr_time.tv_usec / (time_t) 1000)));
}

void	ft_usleep(time_t time)
{
	time_t	start_time;

	start_time = ft_get_current_time();
	while (ft_get_current_time() - start_time < time)
		usleep(500);
}
