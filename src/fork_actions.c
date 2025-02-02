/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_actions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 16:53:22 by fvizcaya          #+#    #+#             */
/*   Updated: 2025/01/08 19:27:25 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
 /*
static t_bool	ft_l_fork_free(t_dinner *dinner, t_philo *philo)
{
	int 	l_fork_num;
	t_bool	ret;

	ret = false;
	l_fork_num = philo->id - 1;
	pthread_mutex_lock(&dinner->forks[l_fork_num]);
	if (!dinner->forks[l_fork_num])
		ret = true;
	return (ret);
}

static t_bool	ft_r_fork_free(t_dinner *dinner, t_philo *philo)
{
	int 	r_fork_num;
	t_bool	ret;

	ret = false;
	r_fork_num = philo->id;
	pthread_mutex_lock(&dinner->mutex_forks);
	if (!dinner->forks[r_fork_num])
		ret = true;
	return (ret);
}
*/
static void	ft_get_for_number(int *left, int *right, t_dinner *dinner, t_philo *philo)
{
	*left = philo->id;
	*right = (philo->id + 1) % dinner->args.num_philos;
	if (philo->id % 2)
	{
		*left = (philo->id + 1) % dinner->args.num_philos;
		*right = philo->id;
	}
}

int	ft_pickup_forks(t_dinner *dinner, t_philo *philo)
{
	int	l_fork_num;
	int	r_fork_num;

	l_fork_num = 0;
	r_fork_num = 0;
	ft_get_for_number(&l_fork_num, &r_fork_num);
}
int	ft_pickup_l_fork(t_dinner *dinner, t_philo *philo)
{
	int	l_fork_num;

	l_fork_num = philo->id - 1;
	pthread_mutex_lock(&dinner->forks[l_fork_num]);
	printf("Soy el philo %d y acabo de coger el tenedor izquierdo.\n", philo->id);
	philo->l_fork = true;
	return (0);
}

int	ft_pickup_r_fork(t_dinner *dinner, t_philo *philo)
{
	int 	r_fork_num;

	r_fork_num = philo->id - 1;
	pthread_mutex_lock(&dinner->forks[r_fork_num]);
	philo->r_fork = true;
	return (0);
}

void	ft_drop_forks(t_dinner *dinner, t_philo *philo)
{
	int	r_fork_num;

	if (philo->id == dinner->args.num_philos)
		r_fork_num = 0;
	else
		r_fork_num = philo->id;
	pthread_mutex_unlock(&dinner->forks[r_fork_num - 1]);
	philo->l_fork = false;
	pthread_mutex_unlock(&dinner->forks[r_fork_num]);
	philo->r_fork = false;
}

