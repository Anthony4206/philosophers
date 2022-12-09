/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 12:23:49 by alevasse          #+#    #+#             */
/*   Updated: 2022/12/09 12:35:12 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>

#include "structs.h"
#include "philo.h"
#include "utils.h"

int	main(int argc, char **argv)
{
	t_ctx	ctx;

	if (argc < 5 || argc > 6 || ft_error(argv))
	{
		ft_putstr_fd("syntax error: number_of_philosophers ", 2);
		ft_putstr_fd("time_to_die time_to_eat time_to_sleep ", 2);
		ft_putstr_fd("[number_of_times_each_philosopher_must_eat]\n", 2);
		return (EXIT_FAILURE);
	}
	ctx = ft_parse(argv);
	ft_create_thread(ctx);
	ft_death(&ctx);
	ft_join_thread(ctx);
	return (EXIT_SUCCESS);
}
