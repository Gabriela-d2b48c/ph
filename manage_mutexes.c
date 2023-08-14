/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_mutexes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriela <gabriela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 09:56:00 by gabriela          #+#    #+#             */
/*   Updated: 2023/08/08 14:08:27 by gabriela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* Initializes the fork mutextes */
int ft_init_fork_mutex(t_simulation *simulation, int number)
{
	while (number < simulation->no_philos)
	{
		simulation->philo[number].number = number;
		if (pthread_mutex_init(&(simulation->philo[number].fork), NULL) != 0)
		{
			printf("Error! Failed to initialize mutex on a fork.\n");
			return (1);
		}
		number++;
	}
	return (0);
}

/* Handling the process of getting own and the other fork.*/
void	ft_get_fork(t_simulation *simulation, int number)
{
	pthread_mutex_lock(&(simulation->philo[number].fork));
	ft_current_status(number, FORK_STATUS, simulation);
	if (number == 0)
		pthread_mutex_lock(&simulation->philo[simulation->no_philos - 1].fork);
	else
		pthread_mutex_lock(&simulation->philo[number - 1].fork);
}

/* Handling the process of putting own and other fork down.*/
void	ft_let_fork(t_simulation *simulation, int number)
{
	pthread_mutex_unlock(&simulation->philo[number].fork);
	if (number == 0)
		pthread_mutex_unlock(&simulation->philo[simulation->no_philos - 1].fork);
	else
		pthread_mutex_unlock(&simulation->philo[number - 1].fork);
}

/* Initialises other mutexes. */
int	ft_init_other_mutex(t_simulation *simulation)
{
	if (pthread_mutex_init(&(simulation->update), NULL) != 0)
	{
		printf("Error! Failed to initialize update mutex\n");
		return (1);
	}
	if (pthread_mutex_init(&(simulation->synchro), NULL) != 0)
	{
		printf("Error! Failed to initialize synchro mutex\n");
		return (1);
	}
	if (pthread_mutex_init(&(simulation->message), NULL) != 0)
	{
		printf("Error! Failed to initialize message mutex\n");
		return (1);
	}
	return (0);
}

/* Destroy used mutexes */
void	ft_mutex_destroy(t_simulation *simulation)
{
	int	number;

	number = 0;
	while (number < simulation->no_philos)
	{
		pthread_mutex_destroy(&(simulation->philo[number].fork));
		number++;
	}
	pthread_mutex_destroy(&(simulation->message));
	pthread_mutex_destroy(&(simulation->synchro));
	pthread_mutex_destroy(&(simulation->update));
}
