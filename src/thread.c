#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#include "structs.h"
#include "philo.h"

void    *ft_philo_func(void *vargp)
{
    (void)vargp;
    usleep(5000000);
    printf("Hello! I'm a philosopher");
    return (NULL);
}

void    *ft_fork_func(void *vargp, void *philos)
{
    (void)vargp;
    while (1)
    {
        if (philos.nb_fork <= 0)
        {
            philos.nb_fork = NB_PHILO;
            printf("fork refell\n");
        }
    }
    return (NULL);
}
