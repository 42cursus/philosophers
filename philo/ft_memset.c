/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 06:58:01 by abelov            #+#    #+#             */
/*   Updated: 2025/01/12 06:58:02 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>

/**
 * ft_memset() fills memory with a constant byte,
 * returns a pointer to the memory area s.
 */
void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*d;

	d = s;
	while (n-- != 0)
		*d++ = (unsigned char)c;
	return (s);
}
