/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriela <gabriela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 11:20:11 by gabriela          #+#    #+#             */
/*   Updated: 2023/08/09 14:28:58 by gabriela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <limits.h>
# include <stdlib.h>
# include <stdint.h>
# include <string.h>
# include <sys/time.h>
# include <sys/types.h>

#define FINISHED "Finished! ʕ•̫͡•ʕ*̫͡*ʕ•͓͡•ʔ-̫͡-ʕ•̫͡•ʔ*̫͡*ʔ-̫͡-ʔ\x1B[0m"
#define DIED     "\x1B[31m (✖╭╮✖)   RIP\x1B[0m"
#define FORK     "\x1B[32m ۜ†\(סּںסּَ` )/ۜ \x1B[0m"
#define EAT      "\x1B[33m( * ◡◡ * ) *munch*\x1B[0m"
#define SLEEP    "\x1B[36m[ { -_-  }] Zzz..\x1B[0m"
#define THINK    "\x1B[35m ( ͠ ° ʖ ͡°)  hmm…\x1B[0m"

# define FORK_STATUS	0
# define EAT_STATUS		1
# define SLEEP_STATUS	2
# define THINK_STATUS	3
# define FULL_STATUS	4
# define DIED_STATUS	5

typedef struct s_philo
{
	pthread_t		thread;
	int				number;
	int				meals_eaten;
	long			last_eaten;
	struct s_simulation	*simulation;
	pthread_mutex_t	fork;
}	t_philo;

typedef struct s_simulation
{
	long			begin;
	int				no_philos;
	int				full;
	int				rip_flag;
	int				full_flag;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_to_eat;
	pthread_t		manager;
	struct s_philo	*philo;
	pthread_mutex_t	message;
	pthread_mutex_t	synchro;
	pthread_mutex_t	update;
}	t_simulation;

// eat_sleep_think
void	ft_eating(t_simulation *simulation, int number);
int		ft_try_eating(int number, t_simulation *simulation);
void	ft_sleeping(int number, t_simulation *simulation);
void	ft_thinking(int number, t_simulation *simulation);

// init_input_main
void	ft_init_philo(t_simulation *simulation, int number);
int		ft_init_mutexes(t_simulation *simulation);
int		ft_check_input(int argc, char *argv[], int input, int error);
int		ft_handle_input(t_simulation *simulation, int argc, char *argv[]);
int		main(int argc, char *argv[]);

// manage_mutexes
int		ft_init_fork_mutex(t_simulation *simulation, int number);
void	ft_get_fork(t_simulation *simulation, int number);
void	ft_let_fork(t_simulation *simulation, int number);
int		ft_init_other_mutex(t_simulation *simulation);
void	ft_mutex_destroy(t_simulation *simulation);

// manage_threads
int		ft_thread_manager(t_simulation *simulation);
void	*ft_manage_end_status(void *void_ptr);
int		ft_thread_creation(t_simulation *simulation);
void	*ft_run_threads(void *void_ptr);
int		ft_thread_joining(t_simulation *simulation, int number);

// philo_status
int		ft_check_finish(t_philo *philo);
void	ft_dead_philo(t_simulation *simulation, int number);
void	ft_full_philos(t_simulation *simulation, int number);
int		ft_check_philo_status(t_simulation *simulation, int *number);

// status_message
void	ft_final_status(t_simulation *simulation, int number, int code, long time);
void	ft_current_status(int number, int code, t_simulation *simulation);

//utils
int		ft_isdigit(int c);
int		ft_isint(char *s);
int		ft_atoi(const char *str);
void	ft_usleep(useconds_t microseconds);
long	ft_gettime(void);

#endif