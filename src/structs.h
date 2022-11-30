#ifndef STRUCTS_H
# define STRUCTS_H

# include <pthread.h>

# define NB_PHILO 4

typedef struct s_ctx
{
    int nb_philo;
    int time_die;
    int time_eat;
    int time_sleep;
    int nb_diner;
}       t_ctx;

typedef struct s_philos
{
    int         nb_fork;
    pthread_t   *philo;
    pthread_t   thread_forks;
}               t_philos;

#endif
