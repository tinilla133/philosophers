/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 17:28:50 by fvizcaya          #+#    #+#             */
/*   Updated: 2024/12/29 22:23:53 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_is_dead(t_dinner *dinner)
{
	int	i;

	i = 0;
	while (i < dinner->num_philos)
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
	while (true)
	{
		ft_think(&args->dinner, &args->dinner.philos[i]);
		if (!ft_pickup_forks(&args->dinner, &args->dinner.philos[i]))
		{
			if (!ft_eat(&args->dinner, &args->dinner.philos[i]))
			{
				ft_drop_forks(&args->dinner, &args->dinner.philos[i]);
				ft_sleep(&args->dinner, &args->dinner.philos[i]);
			}
		}
		return (NULL);
	}
}

