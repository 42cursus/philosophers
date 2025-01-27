/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 03:30:07 by abelov            #+#    #+#             */
/*   Updated: 2025/01/12 03:30:07 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <errno.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "philo_defs.h"

int		parse(int argc, char **argv, t_table *table);
void	init(t_table *table);
int		ft_sleep(t_philo *ph);
int		ft_eat(t_philo *ph);
int		ft_start_sim(t_table *table);
void	*start_routine(void *philo);
void	ft_print_status(t_philo *ph, unsigned char status_code);
void	*ft_monitor(void *arg);
int		sim_is_active(t_table *t);
void	set_sim_end(t_table *t);
int		ft_update_meal_time(t_philo *ph, u_long time);

/* utils */
int		ft_isspace(int c);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_tolower(int c);
u_long	ft_strtoul(const char *nptr, char **endptr, int base);
void	ft_usleep(u_int64_t time);
u_long	ft_get_time(void);
u_long	ft_get_start_time(t_table *table);
void	ft_perror(const char *msg, const char *end);
char	*ft_uitoa_buf(unsigned int abs, char *buf, size_t length);
void	*ft_memset(void *s, int c, size_t n);
size_t	ft_strlen(const char *str);
size_t	ft_strnlen(const char *str, size_t size);
size_t	ft_strlcat(char *dest, const char *src, size_t size);

#endif //PHILO_H
