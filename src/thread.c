#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

#include "structs.h"
#include "philo.h"

double  ft_time(void)
{
    struct timeval  time;

    gettimeofday(&time, NULL);
    return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void    ft_eat(t_philos *philo)
{
    pthread_mutex_lock(&philo->fork_l);
    pthread_mutex_lock(&philo->fork_r);
	printf("%.0f %d has taken a fork\n", ft_time(), philo->philo);
	printf("%.0f %d has taken a fork\n", ft_time(), philo->philo);
	printf("%.0f %d is eating\n", ft_time(), philo->philo);
    usleep(philo->time_eat * 1000);
    pthread_mutex_unlock(&philo->fork_l);
    pthread_mutex_unlock(&philo->fork_r);
}

void    *ft_philo_func(void *philo)
{
    t_philos    *res;
    int         nb_diner;

    res = (t_philos *)philo;
    nb_diner = 0;
    while (1)
    {
        ft_eat(philo);
        nb_diner++;
//        ft_sleep(philo);
    }
    return (NULL);
}
