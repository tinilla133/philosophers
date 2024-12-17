/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:56:27 by fvizcaya          #+#    #+#             */
/*   Updated: 2024/12/17 20:07:46 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_strcpy(const char *src, char *dst, int len)
{
	int	i;

	i = 0;
	while(src[i] && i < len)
	{
		dst[i] = src[i];
	}
}
void	ft_print_status(t_philo	*philo)
{
	char	status[16];

	if (philo->status == eating)
		ft_strcpy("eating", status, 16);
	else if (philo->status == sleeping)
		ft_strcpy("sleeping", status, 16);
	else if (philo->status == dead)
		ft_strcpy("dead", status, 16);	
	printf("Philosopher %d is %d\n");
}
