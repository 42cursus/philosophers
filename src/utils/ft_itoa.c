/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 18:29:05 by abelov            #+#    #+#             */
/*   Updated: 2023/11/18 20:23:59 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	*ft_uitoa_buf(unsigned int nbr, char *buf, size_t length)
{
	char *const			ptr = buf;
	unsigned int const	decimal_radix = 10;
	unsigned int		stack[20];
	unsigned int		ss;

	ss = 0;
	stack[ss++] = nbr;
	while (ss)
	{
		nbr = stack[--ss];
		if (nbr >= decimal_radix)
		{
			stack[ss++] = nbr % decimal_radix;
			stack[ss++] = nbr / decimal_radix;
		}
		else if (length--)
			*buf++ = (char)nbr + '0';
	}
	return (ptr);
}

static size_t	get_int_buf_size(int nb)
{
	size_t		size;
	int const	decimal_radix = 10;

	size = !nb;
	if (nb < 0)
		size++;
	while (nb)
	{
		nb /= decimal_radix;
		size++;
	}
	return (++size);
}

char	*ft_itoa_buf(int nb, char *buf, size_t length)
{
	const char			*save = buf;
	unsigned int		abs;
	int const			mask = nb >> (sizeof(int) * CHAR_BIT - 1);

	abs = (nb + mask) ^ mask;
	if (nb < 0 && length--)
		*buf++ = '-';
	ft_uitoa_buf(abs, buf, length);
	return ((char *)save);
}

/**
 * https://stackoverflow.com/questions/25848815/
 * Allocates (with malloc(3)) and returns a string representing the integer
 * received as an argument.
 *
 * Returns the string representing the integer. NULL if the allocation fails.
 */
char	*ft_itoa(int nb)
{
	char				*buf;
	size_t				buf_size;

	buf_size = get_int_buf_size(nb);
	buf = (char *)malloc(sizeof(char) * buf_size);
	if (!buf)
		return (NULL);
	ft_memset(buf, 0, buf_size * sizeof(char));
	return (ft_itoa_buf(nb, buf, buf_size));
}
