/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 15:51:52 by fvizcaya          #+#    #+#             */
/*   Updated: 2025/02/27 21:16:51 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	ft_inint_args(t_args *args)
{
	args->num_philos = 0;
	args->time_to_die = 0;
	args->time_to_eat = 0;
	args->time_to_sleep = 0;
	args->times_must_eat = 0;
}

static int  ft_alloc_program(t_program *program)
{
    program->args = malloc (sizeof (t_args));
    if (!program->args)
        return (-1);
    program->dinner = malloc (sizeof (t_dinner));
    if (!program->dinner)
    {
        free (program->args);
        return (-1);
    }
    return (0);
}

int	main(int argc, char **argv)
{
	t_program	program;

    if (ft_alloc_program(&program) == -1)
        return (0);
    ft_inint_args(program.args);
	if (ft_parse_args(argc, argv, program.args) == -1)
	{
		printf("Arguments error.\n");
		return (0);
	}
	ft_init(&program);
	// Comenzar la cena
	// Terminar la cena, join de hilos, liberar memoria.
	ft_stop_dinner(&program);
}
