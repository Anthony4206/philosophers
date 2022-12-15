/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 12:26:01 by alevasse          #+#    #+#             */
/*   Updated: 2022/12/15 13:45:42 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <pthread.h>

struct	s_ctx;

typedef struct s_philos
{
	int				philo;
	int				nb_diner;
	long int		*last_diner;
	long int		start;
	pthread_mutex_t	*fork_l;
	pthread_mutex_t	*fork_r;
	pthread_mutex_t	*print;
	struct s_ctx	*rules;
}					t_philos;

typedef struct s_thread
{
	pthread_t		*th;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*print;
	pthread_mutex_t	*die;
	pthread_mutex_t	*end;
}					t_thread;

typedef struct s_ctx
{
	int			nb_philo;
	int			time_die;
	int			time_eat;
	int			time_sleep;
	int			nb_diner;
	int			is_die;
	long int	start;
	t_thread	ths;
	t_philos	*philo;
}				t_ctx;

#endif
