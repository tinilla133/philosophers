/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 15:51:52 by fvizcaya          #+#    #+#             */
/*   Updated: 2024/12/25 14:15:43 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_dinner(t_dinner *dinner)
{
	
}

int	main(int argc, char **argv)
{
	/*
	Parsear.
	Inicializar valores.
	Crear el hilo dispatcher.
	Crear los hilos filósofos.
	*/
	t_dinner	dinner;

	if (ft_parse_args(argc, argv, &dinner.args) == -1)
		return (0);
		ft_init(&dinner);
		ft_dinner(&dinner);
}
