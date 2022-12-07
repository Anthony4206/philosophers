#ifndef STRUCTS_H
# define STRUCTS_H

# include <pthread.h>

typedef struct s_philos
{
    int             philo;
    int             time_die;
    int             time_eat;
    int             time_sleep;
    int             nb_diner;
    pthread_mutex_t *fork_l;
    pthread_mutex_t *fork_r;
    pthread_mutex_t *on;
}                   t_philos;

typedef struct s_thread
{
    pthread_t       *th;
    pthread_mutex_t *fork;
    pthread_mutex_t *on;
}                   t_thread;

typedef struct s_ctx
{
    int         nb_philo;
    int         time_die;
    int         time_eat;
    int         time_sleep;
    int         nb_diner;
    t_thread    ths;
    t_philos    *philo;
}       t_ctx;

#endif
