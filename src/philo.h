#ifndef PHILO_H
# define PHILO_H

#include "structs.h"

void        *ft_philo_func(void *vargp);
t_thread    ft_init_th(t_ctx ctx);
t_philos    *ft_init_philo(t_ctx *ctx, t_thread ths);
void        ft_init(t_ctx ctx);
t_ctx       ft_parse(char **argv);
long int    ft_time(void);

#endif
