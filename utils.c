/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   11_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriela <gabriela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 16:00:12 by gabriela          #+#    #+#             */
/*   Updated: 2023/08/08 13:41:32 by gabriela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philosophers.h"

/* Return 1 if c is a digit, 0 otherwise */
int	ft_isdigit(int c)
{
	if (c == '-' || ('0' <= c && c <= '9'))
		return (1);
	return (0);
}

/* Return 1 if s is a numeric string, 0 otherwise */
int	ft_isint(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (ft_isdigit(s[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	int	sign;
	int	result;

	sign = 1;
	result = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	while ((*str == '-') || (*str == '+'))
	{
		if (*(str + 1) == '-' || *(str + 1) == '+')
			return (0);
		else if (*str == '-')
			sign = sign * (-1);
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + *str - '0';
		str++;
	}
	return (sign * result);
}

/* Suspend for at least no. of microseconds int the argument. */
void	ft_usleep(useconds_t microseconds)
{
	long	time;

	time = ft_gettime();
	while (ft_gettime() < (time + microseconds))
		usleep(500);
}

/* Get the current time in milliseconds. tv.tv_sec is the number
of seconds since 00:00:00 UTC, January 1, 1970, tv.tv_usec is 
the number of microseconds after the last second. */
long	ft_gettime(void)
{
	struct timeval	time;
	int				milliseconds;

	gettimeofday(&time, NULL);
	milliseconds = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (milliseconds);
}
