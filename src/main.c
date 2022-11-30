#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>

#include "structs.h"
#include "philo.h"

int main(int argc, char **argv)
{
	t_ctx	ctx;

	if (argc < 5 || argc > 6)
	{
		printf("syntax error: number_of_philosophers time_to_die time_to_eat \
		time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		return (-1);
	}
	ctx = ft_parse(argc, argv);
    ft_init_thread(ctx);
	return (EXIT_SUCCESS);
}
