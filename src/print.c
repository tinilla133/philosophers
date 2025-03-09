/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:56:27 by fvizcaya          #+#    #+#             */
/*   Updated: 2025/03/05 19:35:20 by fvizcaya         ###   ########.fr       */
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
		i++;
	}
	dst[i] = '\0';
}

void	ft_print_status(t_philo *philo, t_status status)
{
	char	str_status[16];
	time_t	current_time;

	if (status == picking_fork)
		ft_strcpy("has taken a fork", str_status, 16);
	else if (status == eating)
		ft_strcpy("is eating", str_status, 16);
	else if (status == sleeping)
		ft_strcpy("is sleeping", str_status, 16);
	else if (status == thinking)
		ft_strcpy("is thinking", str_status, 16);
	else if (status == dead)
		ft_strcpy("died", str_status, 16);
	current_time = ft_get_current_time();
	printf("%li %d %s\n", current_time, philo->id + 1, str_status);
}
