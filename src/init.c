#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

#include "structs.h"
#include "philo.h"
#include "utils.h"

t_ctx   ft_parse(char **argv)
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
    ret.ths = ft_init_th(ret);
    ret.philo = ft_init_philo(&ret, ret.ths);
    return (ret);
}

t_thread    ft_init_th(t_ctx ctx)
{
    t_thread    *ret;
    int         i;

    ret = ft_calloc(1, sizeof(t_thread));
    ret->th = ft_calloc(ctx.nb_philo, sizeof(pthread_t));
    ret->fork = ft_calloc(ctx.nb_philo, sizeof(pthread_mutex_t));
    ret->on = ft_calloc(1, sizeof(pthread_mutex_t));
    i = -1;
    while (++i < ctx.nb_philo)
        pthread_mutex_init(&ret->fork[i], NULL);
    pthread_mutex_init(ret->on, NULL);    
    return (*ret);
}

t_philos    *ft_init_philo(t_ctx *ctx, t_thread ths)
{
    t_philos    *ret;
    int i;

    ret = ft_calloc(ctx->nb_philo, sizeof(t_philos));
    i = -1;
    while (++i < ctx->nb_philo)
    {
        ret[i].philo = i;
        ret[i].time_die = ctx->time_die;
        ret[i].time_eat = ctx->time_eat;
        ret[i].time_sleep = ctx->time_sleep;
        ret[i].nb_diner = ctx->nb_diner;
        ret[i].fork_l = &ths.fork[i];
        if (!i)
            ret[i].fork_r = &ths.fork[ctx->nb_philo - 1];
        else
            ret[i].fork_r = &ths.fork[i - 1];
        ret[i].on = ths.on;
    }
    return (ret);
}

void    ft_create_thread(t_ctx ctx)
{
    int i;

    i = -1;
    while (++i < ctx.nb_philo)
        pthread_create(&ctx.ths.th[i], NULL, &ft_philo_func, &ctx.philo[i]);
}

void    ft_join_thread(t_ctx ctx)
{
    int i;

    i = -1;
    while (++i < ctx.nb_philo)
        pthread_join(ctx.ths.th[i], NULL);
}

void    ft_init(t_ctx ctx)
{
    ft_create_thread(ctx);
    ft_join_thread(ctx);
}
