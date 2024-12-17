/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 11:18:22 by fvizcaya          #+#    #+#             */
/*   Updated: 2024/12/17 20:06:10 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _PHILO_H_
# define _PHILO_H_

# include <pthread.h>
# include <limits.h>
# include <sys/time.h>

# define MAX_THREADS 61593

typedef struct s_args
{
	int	num_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	times_must_eat;
}				t_args;

typedef struct s_philo
{
	t_status		status;
	int				id;
	pthread_t		thread;
	time_t			last_time_eaten;
	int				times_eaten;
	int				dead;
	int				l_fork;
	int				r_fork;
}					t_philo;

typedef struct s_dinning_r
{
	int 			*forks;
	t_philo			*philos;
	pthread_mutex_t	**m_forks;
	pthread_mutex_t	*screen;
}					t_dinning_r;

typedef enum e_status
{
	eating,
	sleeping,
	dead
}				t_status;

int	ft_parse_args(int argc, char **argv, t_args *args);

#endif