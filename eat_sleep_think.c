/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_think.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriela <gabriela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 09:55:50 by gabriela          #+#    #+#             */
/*   Updated: 2023/08/09 11:09:50 by gabriela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* Handling the case where there is only one philosopher.
Handling the process of tracking the number of meals.*/
int	ft_try_eating(int number, t_simulation *simulation)
{
	if (simulation->no_philos == 1)
	{
		pthread_mutex_lock(&(simulation->philo[number].fork));
		ft_current_status(number, FORK_STATUS, simulation);
		ft_usleep(simulation->time_to_die + 2);
		pthread_mutex_unlock(&(simulation->philo[number].fork));
		return (1);
	}
	else
	{
		ft_get_fork(simulation, number);
		ft_eating(simulation, number);
		ft_let_fork(simulation, number);
		return (0);
	}
}

/* Check if simulation should finish, update eating time, meals eaten
and no. of philosophers that have eaten all meals (if defined) */
void	ft_eating(t_simulation *simulation, int number)
{
	ft_current_status(number, EAT_STATUS, simulation);
	if (ft_check_finish(simulation->philo) == 1)
		return ;
	pthread_mutex_lock(&simulation->update);
	simulation->philo[number].last_eaten = ft_gettime() - simulation->begin;
	simulation->philo[number].meals_eaten++;
	if (simulation->meals_to_eat != -1 && simulation->philo[number].meals_eaten == simulation->meals_to_eat)
		simulation->full++;
	pthread_mutex_unlock(&simulation->update);
	ft_usleep(simulation->time_to_eat);
}

/* Wait as defined in time to sleep arg */
void	ft_sleeping(int number, t_simulation *simulation)
{
	ft_current_status(number, SLEEP_STATUS, simulation);
	ft_usleep(simulation->time_to_sleep);
}

/* Thinking */
void	ft_thinking(int number, t_simulation *simulation)
{
	ft_current_status(number, THINK_STATUS, simulation);
}