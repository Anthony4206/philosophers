/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 12:22:10 by alevasse          #+#    #+#             */
/*   Updated: 2022/12/12 13:13:43 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "structs.h"
#include "utils.h"

void	ft_all_died(t_ctx *ctx)
{
	int	i;

	i = -1;
	while (++i < ctx->nb_philo)
		ctx->philo[i].rules->is_die = 1;
}

void	ft_death(t_ctx *ctx)
{
	int	i;

	while (ctx->nb_diner)
	{
		i = -1;
		while (++i < ctx->nb_philo && !ctx->is_die)
		{
			pthread_mutex_lock(ctx->ths.die);
			if ((ft_death_diff(ft_time(ctx->start), *(ctx->philo[i].last_diner))
					> ctx->time_die) && *(ctx->nb_diner))
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
