/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mem.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 17:37:56 by abelov            #+#    #+#             */
/*   Updated: 2023/11/18 20:24:23 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * The ft_memcmp() function compares the first n bytes (each interpreted
 * as unsigned char) of the memory areas s1 and s2.
 * returns an integer less than, equal to, or greater than zero if the first n
 * bytes of s1 is found, respectively, to be less than, to match, or be greater
 * than the first n bytes of s2. For a nonzero return  value,
 * the sign is determined by the sign of the difference between the first pair
 * of bytes (interpreted as unsigned char) that differ in s1 and s2.
 * If n is zero, the return value is zero.
 *
 * Do not use memcmp() to compare security critical data.
 */
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	while (n-- > 0)
	{
		if (*(unsigned char *)s1 != *(unsigned char *)s2)
			return (*(unsigned char *)s1 - *(unsigned char *)s2);
		s1++;
		s2++;
	}
	return (0);
}
