/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriela <gabriela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:59:56 by gabriela          #+#    #+#             */
/*   Updated: 2023/08/08 14:34:52 by gabriela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philosophers.h"

/* Thread to check on other threads */
int	ft_thread_manager(t_simulation *simulation)
{
	if (pthread_create(&(simulation->manager), NULL, &ft_manage_end_status, simulation) != 0)
	{
		printf("Error! Failed to create manager thread\n");
		return (1);
	}
	return (0);
}

/* Creates a thread for each philo. */
int ft_thread_creation(t_simulation *simulation)
{
	int	number;

	number = 0;
	pthread_mutex_lock(&(simulation->synchro));
	while (number < simulation->no_philos)
	{
		simulation->philo[number].simulation = simulation;
		if (pthread_create(&(simulation->philo[number].thread), NULL,
				&ft_run_threads, &(simulation->philo[number])) != 0)
		{
			printf("Error! Failed to create philo thread.\n");
			return (1);
		}
		number++;
	}
	simulation->begin = ft_gettime();
	pthread_mutex_unlock(&(simulation->synchro));
	return (0);
}

/* Keep checking if the simulation should end and print status if so */
void	*ft_manage_end_status(void *void_ptr)
{
	t_simulation	*simulation;
	int		i;
	int		should_terminate;

	should_terminate = 0;
	i = 0;
	simulation = (t_simulation *)void_ptr;
	while (!should_terminate)
	{
		pthread_mutex_lock(&(simulation->update));
		should_terminate = ft_check_philo_status(simulation, &i);
	}
	return (NULL);
}

/* Synchronize all threads, make every other philo start to think first to
avoid fork deadlock, while the rest tries to eat->sleep->think until the end */
void	*ft_run_threads(void *void_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)void_ptr;
	pthread_mutex_lock(&(philo->simulation->synchro));
	pthread_mutex_unlock(&(philo->simulation->synchro));
	if ((philo->number % 2) == 0 && philo->simulation->no_philos != 1)
	{
		ft_thinking(philo->number, philo->simulation);
		ft_usleep(philo->simulation->time_to_eat - 1);
	}
	while (ft_check_finish(philo) == 0)
	{
		if (ft_try_eating(philo->number, philo->simulation) == 1)
			break ;
		ft_sleeping(philo->number, philo->simulation);
		ft_thinking(philo->number, philo->simulation);
	}
	return (NULL);
}

/* Join all threads, destroy mutexes and free memory */
int	ft_thread_joining(t_simulation *simulation, int number)
{
	if (number < simulation->no_philos)
	{
		if (pthread_join(simulation->philo[number].thread, NULL) != 0)
		{
			printf("Error! Failed to join philo thread\n");
			return (1);
		}
		return ft_thread_joining(simulation, number + 1);
	}
	if (pthread_join(simulation->manager, NULL) != 0)
	{
		printf("Error! Failed to join manager thread\n");
		return (1);
	}
	ft_mutex_destroy(simulation);
	free(simulation->philo);
	simulation->philo = NULL;
	return (0);
}
