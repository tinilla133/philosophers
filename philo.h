/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 11:18:22 by fvizcaya          #+#    #+#             */
/*   Updated: 2025/02/27 19:47:59 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _PHILO_H_
# define _PHILO_H_

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <limits.h>                 
# include <sys/time.h>
# include <time.h>

# define MAX_THREADS 61593

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
	int				action_time;
	pthread_mutex_t	mutex_time;
	int				last_meal_time;
	int				num_meals;
	int				l_fork;
	int				r_fork;
	t_bool			dead;
}				t_philo;

typedef struct s_dinner
{
	pthread_mutex_t	*forks;
	t_args			args;
	t_philo			*philos;
	int				took_last_meal;
	int				action_time;
	t_bool			end_of_dinner;
	pthread_t		dispatcher;
	pthread_mutex_t	mutex_dinner;
	pthread_mutex_t	mutex_counter;
}				t_dinner;

typedef struct s_program
{
	t_philo			*philo;
	t_dinner		*dinner;
	t_args			*args;
	pthread_mutex_t	std_out;
}				t_program;

int				ft_parse_args(int argc, char **argv, t_args *args);
int				ft_init(t_program *program);
long int		ft_get_current_time(void);
void			*ft_philo(void *ptr);
void			ft_eat(t_program *program);
void			ft_sleep(t_program *program);
void			ft_think(t_program *program);
void			ft_pickup_forks(t_program *program);
void			ft_drop_forks(t_program *program);
void			ft_print_status(t_program *program);
void			*ft_dinner(void *ptr);
void			ft_stop_dinner(t_program *program);

#endif