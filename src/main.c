/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 15:51:52 by fvizcaya          #+#    #+#             */
/*   Updated: 2024/12/29 22:26:36 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	
	/*
	Parsear.
	Inicializar valores.
	Crear el hilo dispatcher.
	Crear los hilos filósofos.
	*/
	t_philoargs	philoargs;

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
