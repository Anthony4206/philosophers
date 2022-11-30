#include <stdio.h>
#include <pthread.h>

#include "structs.h"
#include "philo.h"

t_ctx   ft_parse(int argc, char **argv)
{
    t_ctx   ret;

    ret.nb_philo = ft_atoi(argv[1]);
    ret.time_die = ft_atoi(argv[2]);
    ret.time_eat = ft_atoi(argv[3]);
    ret.time_sleep = ft_atoi(argv[4]);
    if (argv[5])
        ret.nb_diner = ft_atoi(argv[5]);
    else
        ret.nb_diner = 0;
    return (ret);
}

void    ft_init_thread(t_ctx ctx)
{
    
}
