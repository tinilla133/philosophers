/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 11:18:22 by fvizcaya          #+#    #+#             */
/*   Updated: 2025/02/06 20:53:38 by fvizcaya         ###   ########.fr       */
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
	pthread_mutex_t	philo_mutex;
	int				id;
	pthread_t		thread;
	pthread_mutex_t mutex_timer;
	int				action_timer;
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
	t_bool			end_of_dinner;
	pthread_t		dispatcher;
	pthread_mutex_t	mutex_dispatcher;
	pthread_mutex_t	mutex_dinner;
	pthread_mutex_t	std_out;
}				t_dinner;

typedef struct s_philoargs
{
	t_dinner	dinner;
	int			philo_num;
}				t_philoargs;

int		ft_parse_args(int argc, char **argv, t_args *args);
int		ft_init(t_philoargs *philoargs);
int		ft_get_current_time(void);
void	*ft_philo(void *ptr);
int		ft_eat(t_dinner *dinner, t_philo *philo);
void	ft_sleep(t_dinner *dinner, t_philo *philo);
void	ft_think(t_dinner *dinner, t_philo *philo);
int		ft_pickup_forks(t_dinner *dinner, t_philo *philo);
void	ft_drop_forks(t_dinner *dinner, t_philo *philo);
void	ft_print_status(t_philo	*philo, pthread_mutex_t *std_out);
void	*ft_dispatcher(void *ptr);
t_bool	ft_end_of_dinner(t_dinner *dinner);
void	ft_stop_dinner(t_dinner *dinner);

#endif/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 13:43:31 by fvizcaya          #+#    #+#             */
/*   Updated: 2025/02/06 21:05:49 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	ft_wait_a_while(const t_dinner *dinner, int time)
{
	int	init_timer;

	init_timer = ft_get_current_time();
	// printf("El tiempo en la función de esperar: %d\n", time);
	while (init_timer - time <= dinner->args.time_to_eat)
	{
		time = ft_get_current_time();
	}
}

int	ft_eat(t_dinner *dinner, t_philo *philo)
{
	// philo->status = eating; 
	// printf("Entra\n");
	pthread_mutex_lock(&philo->mutex_timer);
	philo->action_timer = 0;
	philo->status = eating;
	dinner->took_last_meal = philo->id;
	ft_print_status(philo, &dinner->std_out);
	ft_wait_a_while((const t_dinner *) dinner, dinner->args.time_to_eat);
	// printf("come\n");
	philo->num_meals++;
	philo->last_meal_time = ft_get_current_time();
	pthread_mutex_unlock(&philo->mutex_timer);
	pthread_mutex_unlock(&dinner->forks[philo->l_fork]);
	// printf("Soy el philo %d y acabo de soltar el tenedor izquierdo.\n", philo->id);
	pthread_mutex_unlock(&dinner->forks[philo->r_fork]);
	// printf("Soy el philo %d y acabo de coger el tenedor derecho.\n", philo->id);
	return (0);
}

void	ft_sleep(t_dinner *dinner, t_philo *philo)
{
	philo->status = sleeping;
	pthread_mutex_lock(&philo->mutex_timer);
	philo->action_timer = 0;
	ft_print_status(philo, &dinner->std_out);
	ft_wait_a_while((const t_dinner *) dinner, dinner->args.time_to_sleep);
	philo->status = thinking,
	pthread_mutex_unlock(&philo->mutex_timer);
	ft_think(dinner, philo);
}

void	ft_think(t_dinner *dinner, t_philo *philo)
{
	if (philo->status != thinking)
	{
		philo->status = thinking;
		ft_print_status(philo, &dinner->std_out);
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 11:23:06 by fvizcaya          #+#    #+#             */
/*   Updated: 2025/01/07 19:39:49 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

static int	ft_valid_characters(char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (argv[++i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (-1);
			j++;
		}
	}
	return (0);
}

static int	ft_arg_overflow(char **argv)
{
	if (ft_strlen(argv[1]) > 10)
		return (-1);
	if (ft_strlen(argv[2]) > 19 || ft_strlen(argv[3]) > 19 || \
		ft_strlen(argv[4]) > 19)
		return (-1);
	return (0);
}

static long long	ft_atol(const char *str)
{
	int		sign;
	long	nbr;

	sign = 1;
	nbr = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		nbr = nbr * 10 + *str - 48;
		str++;
	}
	return (nbr * sign);
}

int	ft_parse_args(int argc, char **argv, t_args *args)
{
	if (argc < 5  || argc > 6)
		return (-1);
	if (ft_valid_characters(argv) == -1)
		return (-1);
	if (ft_arg_overflow(argv) == -1)
		return (-1);
	args->num_philos = (int) ft_atol(argv[1]);
	args->time_to_die = (int) ft_atol(argv[2]);
	args->time_to_eat = (int) ft_atol(argv[3]);
	args->time_to_sleep = (int) ft_atol(argv[4]);
	if (argc == 6)
		args->times_must_eat = (int) ft_atol(argv[5]);
	else
		args->times_must_eat = -1;
	// OJO: Número mínimo de filósofos
	if (args->num_philos > INT_MAX || args->time_to_die > INT_MAX || \
		args->time_to_die < 1 || args->time_to_eat > INT_MAX || \
		args->time_to_eat < 1 || args->time_to_sleep > INT_MAX || \
		args->time_to_sleep < 1 || args->times_must_eat > INT_MAX)
		return (-1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 19:20:17 by fvizcaya          #+#    #+#             */
/*   Updated: 2025/01/07 20:57:15 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	ft_end_of_dinner(t_dinner *dinner)
{
	int		i;
	int		curr_time;
	t_bool	ret;

	i = 0;
	ret = false;
	pthread_mutex_lock(&dinner->mutex_dispatcher);
	while (i < dinner->args.num_philos)
	{
		curr_time = ft_get_current_time();
		pthread_mutex_lock(&dinner->std_out);
		printf("Tiempo sin comer del philo %d: %d\n", i + 1, curr_time - dinner->philos[i].last_meal_time);
		pthread_mutex_unlock(&dinner->std_out);
		if ((curr_time - dinner->philos[i].last_meal_time) > \
			dinner->args.time_to_die)
		{
			dinner->philos[i].status = dead;
			ret = true;
		}
		if (dinner->philos[i].num_meals == dinner->args.times_must_eat)
			ret = true;
		i++;
	}
	pthread_mutex_unlock(&dinner->mutex_dispatcher);
	return (ret);
}

void	*ft_dispatcher(void *ptr)
{
	t_dinner	*dinner;

	dinner = (t_dinner *) ptr;
	pthread_mutex_lock(&dinner->mutex_dispatcher);
	while (!dinner->end_of_dinner)
	{
		pthread_mutex_lock(&dinner->std_out);
		printf("====> Hilo dispatcher <====\n");
		pthread_mutex_unlock(&dinner->std_out);
		dinner->end_of_dinner = ft_end_of_dinner(dinner);
		printf("end_of_dinner =====> %d\n", dinner->end_of_dinner);
	}
	pthread_mutex_unlock(&dinner->mutex_dispatcher);
	ft_stop_dinner(dinner);
	return (NULL);
}

void	ft_stop_dinner(t_dinner *dinner)
{
	int	i;

	pthread_mutex_lock(&dinner->std_out);
	printf("========> Entramos en ft_stop_dinner()\n");
	pthread_mutex_unlock(&dinner->std_out);

	i = 0;
	while (i < dinner->args.num_philos)
	{
		pthread_mutex_destroy(&dinner->forks[i]);
		pthread_join(dinner->philos[i++].thread, NULL);
	}
	pthread_mutex_destroy(&dinner->mutex_dinner);
	pthread_mutex_destroy(&dinner->mutex_dispatcher);
	pthread_exit(NULL);
	free (dinner->philos);
	free (dinner->forks);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_actions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 16:53:22 by fvizcaya          #+#    #+#             */
/*   Updated: 2025/02/06 21:05:20 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	ft_pickup_forks(t_dinner *dinner, t_philo *philo)
{
	// printf("l_fork_num ======> %d\n", philo->l_fork);
	// printf("r_fork_num ======> %d\n", philo->r_fork);
	pthread_mutex_lock(&dinner->mutex_dinner);
	if (philo->id == dinner->took_last_meal)
	{
		pthread_mutex_unlock(&dinner->mutex_dinner);
		ft_think(dinner, philo);
	}
	pthread_mutex_unlock(&dinner->mutex_dinner);
	pthread_mutex_lock(&dinner->forks[philo->l_fork]);
	philo->status = picking_fork;
	ft_print_status(philo, &dinner->std_out);
	pthread_mutex_lock(&dinner->forks[philo->r_fork]);
	ft_print_status(philo, &dinner->std_out);
	return (0);
}

void	ft_drop_forks(t_dinner *dinner, t_philo *philo)
{
	pthread_mutex_unlock(&dinner->forks[philo->l_fork]);
	pthread_mutex_unlock(&dinner->forks[philo->r_fork]);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 19:37:17 by fvizcaya          #+#    #+#             */
/*   Updated: 2025/02/06 21:19:28 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_alloc_data_structs(t_args args, t_dinner *dinner)
{
	dinner->forks = (pthread_mutex_t *) malloc ((args.num_philos) * \
		sizeof (pthread_mutex_t));
	if (!dinner->forks)
		return (-1);
	dinner->philos = (t_philo *) malloc ((args.num_philos) * \
					sizeof (t_philo));
	if (!dinner->philos)
		return (-1);
	return (0);
}

static void	ft_init_forks(t_dinner *dinner)
{
	int	i;

	i = 0;
	while (i < (dinner->args.num_philos - 1))
		pthread_mutex_init(&dinner->forks[i++], NULL);
}

static void	ft_get_fork_number(const t_dinner *dinner, t_philo *philo)
{
	if (!(philo->id % 2))
	{
		philo->r_fork = (philo->id + 1) % dinner->args.num_philos;
		philo->l_fork = philo->id;
	}
	else
	{
		philo->l_fork = (philo->id + 1) % dinner->args.num_philos;
		philo->r_fork = philo->id;
	}
}


static void	ft_init_philos(t_dinner *dinner)
{
	int	i;

	i = 0;
	while (i < dinner->args.num_philos)
	{
		dinner->philos[i].id = i;
		dinner->philos[i].dead = false;
		dinner->philos[i].last_meal_time = ft_get_current_time();
		dinner->philos[i].num_meals = 0;
		// dinner->philos[i].status = thinking;
		ft_get_fork_number((const t_dinner *) dinner, &dinner->philos[i]);
		i++;
	}
}

static void	ft_create_threads(t_philoargs *args)
{
	int	i;

	pthread_create(&args->dinner.dispatcher, NULL, ft_dispatcher, \
					&args->dinner);
	i = 0;
	while (i < args->dinner.args.num_philos)
	{
		printf("Num philos: %d\n", args->dinner.args.num_philos);
		args->philo_num = i;
		pthread_create(&args->dinner.philos[i].thread, \
						NULL, ft_philo, args);
		i++;
	}
	printf("Retornamos de ft_create_threads()\n");
}

int	ft_init(t_philoargs *args)
{
	if (ft_alloc_data_structs(args->dinner.args, &args->dinner) == -1)
		return (-1);
	args->dinner.took_last_meal = args->philo_num;
	args->dinner.end_of_dinner = false;
	ft_init_forks(&args->dinner);
	ft_init_philos(&args->dinner);
	pthread_mutex_init(&args->dinner.mutex_dinner, NULL);
	pthread_mutex_init(&args->dinner.mutex_dispatcher, NULL);
	ft_create_threads(args);
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 15:51:52 by fvizcaya          #+#    #+#             */
/*   Updated: 2025/02/05 20:53:27 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	ft_inint_args(t_args *args)
{
	args->num_philos = 0;
	args->time_to_die = 0;
	args->time_to_eat = 0;
	args->time_to_sleep = 0;
	args->times_must_eat = 0;
}

int	main(int argc, char **argv)
{
	/*
	Parsear.
	Inicializar valores.
	Crear el hilo dispatcher.
	Crear los hilos filósofos.
	*/
	t_philoargs	philoargs;

	ft_inint_args(&philoargs.dinner.args);
	if (ft_parse_args(argc, argv, &philoargs.dinner.args) == -1)
	{
		printf("Arguments error.\n");
		return (0);
	}
	ft_init(&philoargs);
	// Comenzar la cena
	// Terminar la cena, join de hilos, liberar memoria.
	ft_stop_dinner(&philoargs.dinner);
}
#!/bin/bash

for i in *; do
	cat $i >> copilot.c
done
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 17:28:50 by fvizcaya          #+#    #+#             */
/*   Updated: 2025/02/06 21:19:00 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_is_dead(t_dinner *dinner)
{
	int	i;

	i = 0;
	while (i < dinner->args.num_philos)
	{
		if (dinner->philos[i].status == dead)
			return (1);
		i++;
	}
	return (0);
}

void	*ft_philo(void *ptr)
{
	t_philoargs	*args;
	int			i;

	args = (t_philoargs *) ptr;
	i = args->philo_num;
	/*
	********** Coger tenedores *************
	
	Recorremos todos los filósofos. Y vamos haciendo que cojan tenedores.
	Si no pueden cogerlos, recorremos todos los filósofos y, al que menos tiempo 
	le quede para morir de los que están pensando,
	lo almacenamos en la variable prioritary de t_dinner dinner (si hubiera un 
	empate, no se cambia la variable). Así, insistiremos con ése hasta que pueda tomar 
	ambos tenedores.

	************ Comer **********************
	************ Soltar tenedores ***********

	********** Dormir ********************

	Cuando un filósofo termina de comer (ft_eat devuelve cero) se le manda a dormir.
	Un filósofo siempre puede ir a dormir, puesto que no necesita nada para ello.
	// Coger tenedores
	// Comer
	// Dormir
	********** Pensar ********************

	No hay ninguna condición de orden ni de tiempo en el subject para pensar, por tanto, 
	consideramos que cuando un filósofo no está comiendo ni durmiendo, está pensando.
	*/
	usleep(1000);
	if (!(args->philo_num % 2))
		ft_think(&args->dinner, &args->dinner.philos[i]);
	while (true)
	{
		// printf("¡Hola!, soy el philo %d\n", i);
		ft_pickup_forks(&args->dinner, &args->dinner.philos[i]);
		ft_eat(&args->dinner, &args->dinner.philos[i]);
		// ft_drop_forks(&args->dinner, &args->dinner.philos[i]);
		ft_sleep(&args->dinner, &args->dinner.philos[i]);
		ft_think(&args->dinner, &args->dinner.philos[i]);
	}
	return (NULL);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:56:27 by fvizcaya          #+#    #+#             */
/*   Updated: 2025/01/07 20:35:49 by fvizcaya         ###   ########.fr       */
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

void	ft_print_status(t_philo	*philo, pthread_mutex_t *std_out)
{
	char	status[16];

	if (philo->status == picking_fork)
		ft_strcpy("has taken a fork", status, 16);
	if (philo->status == eating)
		ft_strcpy("is eating", status, 16);
	else if (philo->status == sleeping)
		ft_strcpy("is sleeping", status, 16);
	else if (philo->status == thinking)
		ft_strcpy("is thinking", status, 16);
	else if (philo->status == dead)
		ft_strcpy("died", status, 16);
	pthread_mutex_lock(std_out);
	printf("%d %d %s\n", ft_get_current_time(), philo->id + 1, status);
	usleep(500000);
	pthread_mutex_unlock(std_out);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 14:41:58 by fvizcaya          #+#    #+#             */
/*   Updated: 2025/01/07 20:38:34 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

inline int	ft_get_current_time(void)
{
	struct timeval	curr_time;

	gettimeofday(&curr_time, NULL);
	return ((int) curr_time.tv_sec + (curr_time.tv_usec / 1000));
}
