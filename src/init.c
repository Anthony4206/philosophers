/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 12:29:01 by alevasse          #+#    #+#             */
/*   Updated: 2022/12/12 13:15:29 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

#include "structs.h"
#include "philo.h"
#include "utils.h"

void	ft_free(t_ctx ctx)
{
	free(ctx.ths.th);
	free(ctx.ths.fork);
	free(ctx.ths.print);
	free(ctx.ths.die);
	free(ctx.philo);
}

t_ctx	ft_parse(char **argv)
{
	t_ctx			ret;
	struct timeval	tv;

	ret.nb_philo = ft_atoi(argv[1]);
	ret.time_die = ft_atoi(argv[2]);
	ret.time_eat = ft_atoi(argv[3]);
	ret.time_sleep = ft_atoi(argv[4]);
	if (argv[5])
		ret.nb_diner = ft_atoi(argv[5]);
	else
		ret.nb_diner = -1;
	ret.is_die = 0;
	gettimeofday(&tv, NULL);
	ret.start = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	ret.ths = ft_init_th(ret);
	ret.philo = ft_init_philo(&ret, ret.ths);
	return (ret);
}

t_thread	ft_init_th(t_ctx ctx)
{
	t_thread	ret;
	int			i;

	ret.th = ft_calloc(ctx.nb_philo, sizeof(pthread_t));
	ret.fork = ft_calloc(ctx.nb_philo, sizeof(pthread_mutex_t));
	ret.print = ft_calloc(1, sizeof(pthread_mutex_t));
	ret.die = ft_calloc(1, sizeof(pthread_mutex_t));
	ret.end = ft_calloc(1, sizeof(pthread_mutex_t));
	i = -1;
	while (++i < ctx.nb_philo)
		pthread_mutex_init(&ret.fork[i], NULL);
	pthread_mutex_init(ret.print, NULL);
	pthread_mutex_init(ret.die, NULL);
	pthread_mutex_init(ret.end, NULL);
	return (ret);
}

t_philos	*ft_init_philo(t_ctx *ctx, t_thread ths)
{
	t_philos	*ret;
	int			i;

	ret = ft_calloc(ctx->nb_philo, sizeof(t_philos));
	i = -1;
	while (++i < ctx->nb_philo)
	{
		ret[i].philo = i;
		ret[i].last_diner = ft_calloc(1, sizeof(long int));
		ret[i].rules = ctx;
		ret[i].start = ctx->start;
		ret[i].fork_l = &ths.fork[i];
		if (!i)
			ret[i].fork_r = &ths.fork[ctx->nb_philo - 1];
		else
			ret[i].fork_r = &ths.fork[i - 1];
		ret[i].print = ths.print;
	}
	return (ret);
}
