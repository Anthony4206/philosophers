/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 12:22:10 by alevasse          #+#    #+#             */
/*   Updated: 2022/12/15 13:38:16 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "structs.h"
#include "utils.h"

void	ft_terminate_diner(t_philos *philo)
{
	long	round_time;
	long	finish_time;

	round_time = philo->rules->time_eat + philo->rules->time_sleep;
	finish_time = round_time * (philo->rules->nb_diner);
	if (*(philo->last_diner) < (finish_time - philo->rules->time_eat))
	{
		ft_lock_print(philo->rules, philo->philo, "is sleeping");
		ft_usleep(philo->rules, philo->rules->time_sleep * 1000);
		if (philo->rules->time_sleep < philo->rules->time_eat)
			ft_lock_print(philo->rules, philo->philo, "is thinking");
	}
}

void	ft_all_died(t_ctx *ctx)
{
	int	i;

	i = -1;
	while (++i < ctx->nb_philo)
	{
		pthread_mutex_lock(ctx->ths.end);
		ctx->philo[i].rules->is_die = 1;
		pthread_mutex_unlock(ctx->ths.end);
	}
}

void	ft_death(t_ctx *ctx)
{
	int	i;

	while (ctx->nb_diner)
	{
		if (ctx->nb_diner > 0 && (ft_time(ctx->start)
				>= ((ctx->nb_diner - 1) * (ctx->time_eat + ctx->time_sleep)
					+ ctx->time_die)))
			break ;
		i = -1;
		while (++i < ctx->nb_philo && !ctx->is_die)
		{
			pthread_mutex_lock(ctx->ths.die);
			if ((ft_death_diff(ft_time(ctx->start), *(ctx->philo[i].last_diner))
					> ctx->time_die))
			{
				ft_lock_print(ctx->philo[i].rules, ctx->philo[i].philo, "died");
				ctx->is_die = 1;
				ft_all_died(ctx);
			}
			pthread_mutex_unlock(ctx->ths.die);
		}
		if (ctx->is_die)
			break ;
	}
}
