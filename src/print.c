/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:56:27 by fvizcaya          #+#    #+#             */
/*   Updated: 2024/12/24 16:00:47 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_strcpy(const char *src, char *dst, int len)
{
	int	i;

	i = 0;
	while (src[i] && i < len)
	{
		dst[i] = src[i];
	}
}

void	ft_print_status(t_philo	*philo, pthread_mutex_t *std_out)
{
	char	status[16];

	if (philo->status == picking_fork)
		ft_strcpy("is taking a fork", status, 16);
	if (philo->status == eating)
		ft_strcpy("is eating", status, 16);
	else if (philo->status == sleeping)
		ft_strcpy("is sleeping", status, 16);
	else if (philo->status == thinking)
		ft_strcpy("is thinking", status, 16);
	else if (philo->status == dead)
		ft_strcpy("died", status, 16);
	pthread_mutex_lock(std_out);
	printf("%i  %d %s\n", ft_get_current_time(), philo->id, status);
	pthread_mutex_unlock(std_out);
}
