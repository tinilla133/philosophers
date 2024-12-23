/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 17:28:50 by fvizcaya          #+#    #+#             */
/*   Updated: 2024/12/24 00:03:12 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_dinner(t_dinner *dinner)
{

}

void	*philo(void *ptr)
{
	t_dinner	*dinner;
	int			i;

	dinner = (t_dinner *) ptr;
	/*
	********** Coger tenedores *************
	
	Recorremos todos los filósofos. Y vamos haciendo que cojan tenedores.
	Si no pueden cogerlos, recorremos todos los filósofos y, al que menos tiempo 
	le quede para morir de los que están pensando,
	lo almacenamos en la variable prioritary de t_dinner dinner (si hubiera un 
	empate, no se cambia la variable). Así, insistiremos con ése hasta que pueda tomar 
	ambos tenedores.

	********** Dormir ********************

	Cuando un filósofo termina de comer (ft_eat devuelve cero) se le manda a dormir.
	Un filósofo siempre puede ir a dormir, puesto que no necesita nada para ello.
	// Coger tenedores
	// Comer
	// Dormir
	********** Pensar ********************

	A falta de leer el subject al respecto, no creo que haya que poner ninguna condición 
	ni tiempo. Cuando un filósofo no está comiendo ni durmiendo, está pensando.
	*/
	i = 0;
	ft_pickup_fork(dinner, &dinner->philos[i]);
	if (!ft_eat(&dinner->philos[i]))
	{
		ft_drop_forks(dinner, dinner->philos[i]);
		ft_sleep();
	}
}
