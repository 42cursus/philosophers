/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 18:27:13 by abelov            #+#    #+#             */
/*   Updated: 2024/09/13 18:27:13 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <pthread.h>

int	main(int argc, char **argv)
{
	if (argc != 1)
		if (argv != NULL && *argv != NULL)
			ft_printf("%s\n", *argv);
	return (0);
}
