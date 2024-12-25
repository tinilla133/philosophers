/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 11:18:22 by fvizcaya          #+#    #+#             */
/*   Updated: 2024/12/25 14:25:46 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _PHILO_H_
# define _PHILO_H_

# include <pthread.h>
# include <limits.h>                 
# include <sys/time.h>
# include <time.h>    

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
	pthread_mutex_t	philo_mutex;
	int				id;
	pthread_t		thread;
	int				last_meal_time;
	int				times_eaten;
	int				dead;
	int				l_fork;
	int				r_fork;
}					t_philo;

typedef struct s_dinner
{
	int 			num_philos;
	int				*forks;
	t_args			args;
	t_philo			*philos;
	int				prioritary;
	pthread_mutex_t	dispatcher;
	pthread_mutex_t	mtx_forks;
	pthread_mutex_t	mutex_forks;
	pthread_mutex_t	std_out;
}				t_dinner;

typedef enum e_status
{
	picking_fork,
	eating,
	sleeping,
	thinking,
	dead
}			 t_status;

int		ft_parse_args(int argc, char **argv, t_args *args);
int		ft_init(t_dinner *dinner);
int		ft_get_current_time(void);
void	*ft_philo(void *ptr);
int		ft_eat(t_dinner *dinner, t_philo *philo);
void	ft_sleep(t_dinner *dinner, t_philo *philo);
void	ft_think(t_dinner *dinner, t_philo *philo);
int		ft_pickup_fork(t_dinner *dinner, t_philo *philo);
void	ft_drop_forks(t_dinner *dinner, t_philo *philo);
void	ft_print_status(t_philo	*philo, pthread_mutex_t *std_out);

#endif