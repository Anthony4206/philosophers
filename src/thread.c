/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 12:22:52 by alevasse          #+#    #+#             */
/*   Updated: 2022/12/12 13:17:48 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <sys/time.h>

#include "structs.h"
#include "philo.h"
#include "utils.h"

void	ft_create_thread(t_ctx ctx)
{
	int	i;

	i = -1;
	while (++i < ctx.nb_philo)
		pthread_create(&ctx.ths.th[i], NULL, ft_philo_func, &ctx.philo[i]);
	if (ctx.nb_philo % 2)
		printf("%ld %d is thinking\n", ft_time(ctx.start), ctx.nb_philo);
}

void	ft_join_thread(t_ctx *ctx)
{
	int	i;

	i = -1;
	while (++i < ctx->nb_philo)
		pthread_join(ctx->ths.th[i], NULL);
	ctx->nb_diner = 0;
	i = -1;
	while (++i < ctx->nb_philo)
		pthread_mutex_destroy(&ctx->ths.fork[i]);
	pthread_mutex_destroy(ctx->ths.print);
	pthread_mutex_destroy(ctx->ths.die);
}

void	ft_eat(t_philos *philo)
{
	pthread_mutex_lock(philo->fork_l);
	pthread_mutex_lock(philo->fork_r);
	ft_lock_print(philo->rules, philo->philo, "has taken a fork");
	ft_lock_print(philo->rules, philo->philo, "has taken a fork");
	ft_lock_print(philo->rules, philo->philo, "is eating");
	pthread_mutex_lock(philo->rules->ths.die);
	*(philo->last_diner) = ft_time(philo->rules->start);
	pthread_mutex_unlock(philo->rules->ths.die);
	ft_usleep(philo->rules, philo->rules->time_eat * 1000);
	pthread_mutex_unlock(philo->fork_l);
	pthread_mutex_unlock(philo->fork_r);
}

void	*ft_philo_func(void *v_philo)
{
	t_philos	*philo;
	int			nb_diner;

	philo = (t_philos *)v_philo;
	nb_diner = 0;
	if (philo->philo % 2)
	{
		ft_lock_print(philo->rules, philo->philo, "is thinking");
		ft_usleep(philo->rules, 10000);
	}
	while (1)
	{
		ft_eat(philo);
	    pthread_mutex_lock(philo->rules->ths.end);
		if ((++nb_diner && nb_diner == philo->rules->nb_diner)
			|| philo->rules->is_die)
			break ;
	    pthread_mutex_unlock(philo->rules->ths.end);
		ft_lock_print(philo->rules, philo->philo, "is sleeping");
		ft_usleep(philo->rules, philo->rules->time_sleep * 1000);
		ft_lock_print(philo->rules, philo->philo, "is thinking");
	}
	return (NULL);
}
