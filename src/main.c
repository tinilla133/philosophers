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
