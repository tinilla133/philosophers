/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 11:23:06 by fvizcaya          #+#    #+#             */
/*   Updated: 2025/04/01 21:19:51 by fvizcaya         ###   ########.fr       */
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

static int	ft_arg_overflow(char **argv, int argc)
{
	if (ft_strlen(argv[1]) > 10)
		return (-1);
	if (ft_strlen(argv[2]) > 10 || ft_strlen(argv[3]) > 10 || \
		ft_strlen(argv[4]) > 10)
		return (-1);
	if (argc == 6)
		if (ft_strlen(argv[5]) > 10)
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
	if (argc < 5 || argc > 6)
		return (-1);
	if (ft_valid_characters(argv) == -1)
		return (-1);
	if (ft_arg_overflow(argv, argc) == -1)
		return (-1);
	args->num_philos = (int) ft_atol(argv[1]);
	args->time_to_die = (int) ft_atol(argv[2]);
	args->time_to_eat = (int) ft_atol(argv[3]);
	args->time_to_sleep = (int) ft_atol(argv[4]);
	if (argc == 6)
		args->times_must_eat = (int) ft_atol(argv[5]);
	else
		args->times_must_eat = -1;
	if (args->num_philos == 0 || args->times_must_eat == 0)
		return (-1);
	return (0);
}
