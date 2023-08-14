/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriela <gabriela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 09:19:58 by gabriela          #+#    #+#             */
/*   Updated: 2023/08/09 11:24:17 by gabriela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philosophers.h"

/* Check if simulation should finish (philo is dead or everyone's full). */
int	ft_check_finish(t_philo *philo)
{
	int check;

	check = 0;
	pthread_mutex_lock(&(philo->simulation->update));
	if (philo->simulation->rip_flag == 1
		|| philo->simulation->full == philo->simulation->no_philos)
		check = 1;
	pthread_mutex_unlock(&(philo->simulation->update));
	return (check);
}

/* Print death status and unlock update mutex */
void	ft_dead_philo(t_simulation *simulation, int number)
{
	simulation->rip_flag++;
	ft_current_status(number, DIED_STATUS, simulation);
	pthread_mutex_unlock(&(simulation->update));
}

/* Print end status and unlock update mutex */
void	ft_full_philos(t_simulation *simulation, int number)
{
	ft_current_status(number, FULL_STATUS, simulation);
	pthread_mutex_unlock(&(simulation->update));
}

/* Checks the status of the philosophers */
int	ft_check_philo_status(t_simulation *simulation, int *number)
{
	long elapsed_time;

	elapsed_time = ft_gettime() - simulation->begin;
	if (elapsed_time - simulation->philo[*number].last_eaten > simulation->time_to_die)
	{
		ft_dead_philo(simulation, *number);
		return 1;
	}
	if (simulation->no_philos == simulation->full)
	{
		ft_full_philos(simulation, *number);
		return 1;
	}
	pthread_mutex_unlock(&(simulation->update));
	(*number)++;
	if (*number == simulation->no_philos)
	{
		*number = 0;
		ft_usleep(5);
	}
	return 0;
}
