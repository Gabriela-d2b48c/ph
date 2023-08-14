/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_parsing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriela <gabriela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 16:27:54 by gabriela          #+#    #+#             */
/*   Updated: 2023/08/08 14:09:22 by gabriela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philosophers.h"


/* Initializing the philo structure */
void	ft_init_philo(t_simulation *simulation, int number)
{
	while (number < simulation->no_philos)
	{
		simulation->philo[number].last_eaten = 0;
		simulation->philo[number].meals_eaten = 0;
		number++;
	}
}

/* Check if there's correct number of arguments, which are
numeric strings, positive and within INT_MAX. */
int	ft_check_input(int argc, char *argv[], int input, int error)
{
	if (argc != 5 && argc != 6)
		error = 1;
	while (input < argc)
	{
		if (ft_atoi(argv[input]) > INT_MAX || ft_atoi(argv[input]) <= 0
			|| ft_isint(argv[input]) == 1) 
			error = 1;
		input++;
	}
	if (error == 1)
	{
		printf("Error! Wrong input\n");
		return (1);
	}
	return (0);
}

/* Assign values to the simulation members and allocate memory. */
int	ft_handle_input(t_simulation *simulation, int argc, char *argv[])
{
	if (ft_check_input(argc, argv, 1, 0) == 1)
		return (1);
	simulation->no_philos = ft_atoi(argv[1]);
	simulation->time_to_die = ft_atoi(argv[2]);
	simulation->time_to_eat = ft_atoi(argv[3]);
	simulation->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		simulation->meals_to_eat = ft_atoi(argv[5]);
	else
		simulation->meals_to_eat = -1;
	simulation->philo = malloc(sizeof(t_philo) * simulation->no_philos);
	if (simulation->philo == NULL)
	{
		printf("Error! Philo allocation failed\n");
		return (1);
	}
	memset(simulation->philo, 0, sizeof(t_philo) * simulation->no_philos);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_simulation	simulation;

	memset(&simulation, 0, sizeof(t_simulation));
	if (ft_handle_input(&simulation, argc, argv) == 1)
		return (-1);
	if (ft_init_mutexes(&simulation) == 1)
		return (-1);
	ft_thread_creation(&simulation);
	ft_thread_manager(&simulation);
	ft_thread_joining(&simulation, 0);
	return (0);
}

/* Initializes all mutexes. */
int	ft_init_mutexes(t_simulation *simulation)
{
	if (ft_init_fork_mutex(simulation, 0) == 1
		|| ft_init_other_mutex(simulation) == 1)
		return (1);
	ft_init_philo(simulation, 0);
	return (0);
}