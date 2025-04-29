/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 11:18:22 by fvizcaya          #+#    #+#             */
/*   Updated: 2025/04/02 18:33:07 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <limits.h>                 
# include <sys/time.h>
# include <time.h>

# define MAX_THREADS 61593

# define DEBUG_MODE

typedef struct s_dinner		t_dinner;

typedef enum e_bool
{
	false,
	true
}			t_bool;

typedef enum e_status
{
	picking_fork,
	eating,
	sleeping,
	thinking,
	dead
}				t_status;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	time_t			last_meal_time;
	int				num_meals;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	t_dinner		*dinner;
}				t_philo;

typedef struct s_args
{
	int	num_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	times_must_eat;
}				t_args;

typedef struct s_dinner
{
	time_t			init_time;
	t_args			*args;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	t_bool			end_of_dinner;
	pthread_mutex_t	mutex_eating;
	pthread_mutex_t	mutex_time;
	pthread_mutex_t	mutex_end;
	pthread_mutex_t	mutex_stdout;

}				t_dinner;

int				ft_parse_args(int argc, char **argv, t_args *args);
int				ft_init(t_dinner *dinner);
time_t			ft_get_current_time(void);
void			ft_usleep(time_t time);
void			*ft_philo(void *ptr);
int				ft_philo_actions(t_philo *philo);
int				ft_print_status(t_philo *philo, t_status status);
void			ft_dinner(t_dinner *dinner);
int				ft_check_end(t_dinner *dinner);
void			ft_stop_dinner(t_dinner *dinner);

#endif