/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_actions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 16:53:22 by fvizcaya          #+#    #+#             */
/*   Updated: 2025/02/05 21:08:21 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	ft_get_fork_number(int *left, int *right, \
				t_dinner *dinner, t_philo *philo)
{
	if (!(philo->id % 2))
	{
		*left = philo->id;
		*right = (philo->id + 1) % dinner->args.num_philos;
	}
	else
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
	ft_get_fork_number(&l_fork_num, &r_fork_num, dinner, philo);
	printf("l_fork_num ======> %d\n", l_fork_num);
	printf("r_fork_num ======> %d\n", r_fork_num);
	pthread_mutex_lock(&dinner->forks[l_fork_num]);
	philo->status = picking_fork;
	philo->r_fork = true;
	ft_print_status(philo, &dinner->std_out);
	printf("Soy el philo %d y acabo de coger el tenedor izquierdo.\n", philo->id);
	pthread_mutex_lock(&dinner->forks[r_fork_num]);
	philo->l_fork = true;
	ft_print_status(philo, &dinner->std_out);
	printf("Soy el philo %d y acabo de coger el tenedor derecho.\n", philo->id);
	return 0;
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
