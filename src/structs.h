#ifndef STRUCTS_H
# define STRUCTS_H

# include <pthread.h>

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
    int             philo;
    int             time_die;
    int             time_eat;
    int             time_sleep;
    int             nb_diner;
    pthread_mutex_t fork_l;
    pthread_mutex_t fork_r;
}                   t_philos;

typedef struct s_thread
{
    pthread_t       *th;
    pthread_mutex_t *fork;
}                   t_thread;

#endif
