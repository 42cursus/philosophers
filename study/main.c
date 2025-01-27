/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 01:51:10 by abelov            #+#    #+#             */
/*   Updated: 2025/01/27 01:51:10 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

// Define ANSI escape sequences for colors and styles
#define BOLD_CYAN "\033[1;36m"
#define RESET "\033[0m"

int	main(void)
{
	struct timeval	start;
	struct timeval	end;
	long			seconds;
	long			microseconds;
	double			elapsed_milliseconds;

	gettimeofday(&start, NULL);
	usleep(500000);
	gettimeofday(&end, NULL);
	seconds = end.tv_sec - start.tv_sec;
	microseconds = end.tv_usec - start.tv_usec;
	elapsed_milliseconds = (seconds * 1000.0) + (microseconds / 1000.0);
	printf("Expected sleep duration: "BOLD_CYAN""
		"\t500 milliseconds\n"RESET);
	printf("Actual sleep duration: "BOLD_CYAN""
		"\t\t%.2f milliseconds\n\n"RESET, elapsed_milliseconds);
	return (0);
}
