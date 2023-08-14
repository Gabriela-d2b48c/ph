/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_message.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriela <gabriela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 09:19:47 by gabriela          #+#    #+#             */
/*   Updated: 2023/08/09 11:27:31 by gabriela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philosophers.h"

/* Print the respective end status */
void	ft_final_status(t_simulation *simulation, int number, int code, long time)
{
	pthread_mutex_lock(&simulation->message);
	time = ft_gettime() - simulation->begin;
	if (code == FULL_STATUS)
		printf("%ld %s\n", time + simulation->time_to_eat, FINISHED);
	if (code == DIED_STATUS)
		printf("%lu %d died %s\n", time, number + 1, DIED);
}

/* Print the respective current status */
void	ft_current_status(int number, int code, t_simulation *simulation)
{
	long	time;

	time = 0;
	if (code == FULL_STATUS || code == DIED_STATUS)
	{
		ft_final_status(simulation, number, code, time);
		return ;
	}
	if (ft_check_finish(simulation->philo) == 1)
		return ;
	pthread_mutex_lock(&simulation->message);
	time = ft_gettime() - simulation->begin;
	if (code == FORK_STATUS)
		printf("%lu %d has taken a fork %s\n", time, number + 1, FORK);
	if (code == EAT_STATUS)
		printf("%lu %d is eating %s\n", time, number + 1, EAT);
	if (code == SLEEP_STATUS)
		printf("%lu %d is sleeping %s\n", time, number + 1, SLEEP);
	if (code == THINK_STATUS)
		printf("%lu %d is thinking %s\n", time, number + 1, THINK);
	pthread_mutex_unlock(&simulation->message);
}