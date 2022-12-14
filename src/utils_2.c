/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 12:24:04 by alevasse          #+#    #+#             */
/*   Updated: 2022/12/15 12:53:22 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>

#include "structs.h"

long int	ft_diff(struct timeval diff)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (((tv.tv_sec - diff.tv_sec) * 1000000)
		+ (tv.tv_usec - diff.tv_usec));
}

long int	ft_death_diff(long int now, long int last)
{
	return (now - last);
}

void	ft_usleep(t_ctx *rules, long time)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	while (ft_diff(tv) <= time)
	{
		pthread_mutex_lock(rules->ths.end);
		if (rules->is_die)
		{
			pthread_mutex_unlock(rules->ths.end);
			break ;
		}
		pthread_mutex_unlock(rules->ths.end);
		usleep(50);
	}
}

long int	ft_time(long int start)
{
	struct timeval	end;

	gettimeofday(&end, NULL);
	return (end.tv_sec * 1000 + end.tv_usec / 1000 - start);
}

void	ft_lock_print(t_ctx *rules, int philo, char *msg)
{
	pthread_mutex_lock(rules->ths.print);
	if (!rules->is_die)
	{
		printf("%ld ", ft_time(rules->start));
		printf("%d ", philo + 1);
		printf("%s\n", msg);
	}
	pthread_mutex_unlock(rules->ths.print);
}
