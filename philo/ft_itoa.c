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
