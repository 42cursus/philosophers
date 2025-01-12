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
# include <pthread.h>
# include <errno.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "philo_defs.h"

int		parse(int argc, char **argv, t_table *table);
void	init(t_table *table);
int		ft_start_sim(t_table *table);
void	*start_routine(void *philo);
void	ft_print_status(t_philo *ph, char *status);
void	*ft_monitor(void *arg);

/* utils */
int		ft_isspace(int c);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isxdigit(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_isupper(int c);
int		ft_islower(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
long	ft_strtol(const char *nptr, char **endptr, int base);
u_long	ft_strtoul(const char *nptr, char **endptr, int base);
void	ft_usleep(long long int time);
u_long	ft_get_time(void);
void	ft_perror(const char *msg, const char *end);
char	*ft_itoa(int nb);
char	*ft_itoa_buf(int nb, char *buf, size_t length);
char	*ft_uitoa_buf(unsigned int abs, char *buf, size_t length);
void	*ft_memset(void *s, int c, size_t n);
size_t	ft_strlen(const char *str);
#endif //PHILO_H
