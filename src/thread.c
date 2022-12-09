#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <sys/time.h>

#include "structs.h"
#include "philo.h"

long int  ft_time(void)
{
    struct timeval  end;
	static long int start = 0;

    gettimeofday(&end, NULL);
	if (!start)
		start = end.tv_sec * 1000 + end.tv_usec / 1000;
    return (end.tv_sec  * 1000 + end.tv_usec / 1000 - start);
}

void    ft_lock_print(t_ctx *rules, int philo, char *msg)
{
    pthread_mutex_lock(rules->ths.print);
    if (!rules->is_die)
    {
        printf("%ld ", ft_time());
	    printf("%d ", philo + 1);
	    printf("%s\n", msg);
    }
    pthread_mutex_unlock(rules->ths.print);
}

void    ft_eat(t_philos *philo)
{
    pthread_mutex_lock(philo->fork_l);
    pthread_mutex_lock(philo->fork_r);
    ft_lock_print(philo->rules, philo->philo, "has taken a fork");
    ft_lock_print(philo->rules, philo->philo, "has taken a fork");
    ft_lock_print(philo->rules, philo->philo, "is eating");
    usleep(philo->rules->time_eat * 1000);
    pthread_mutex_unlock(philo->fork_l);
    pthread_mutex_unlock(philo->fork_r);
}

void	ft_sleep_and_think(t_philos *philo)
{
    ft_lock_print(philo->rules, philo->philo, "is sleeping");
    usleep(philo->rules->time_sleep * 1000);
    ft_lock_print(philo->rules, philo->philo, "is thinking");
}

void    *ft_philo_func(void *v_philo)
{
    t_philos    *philo;
    int         nb_diner;

    philo = (t_philos *)v_philo;
    nb_diner = 0;
    if (philo->philo % 2)
        usleep(1000);
    while (1)
    {
        ft_eat(philo);
        if (++nb_diner && nb_diner == philo->rules->nb_diner)
            break ;
        ft_sleep_and_think(philo);
    }
    return (NULL);
}
