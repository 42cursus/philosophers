/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isctype.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:04:01 by abelov            #+#    #+#             */
/*   Updated: 2023/11/18 20:23:45 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalpha(int c)
{
	return (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z'));
}

int	ft_isdigit(int c)
{
	return ('0' <= c && c <= '9');
}

/**
 * The ft_tolower() function converts uppercase letters to lowercase.
 * Returns its lowercase equivalent, if a lowercase representation exists
 * in the current locale.  Otherwise, returns c.
 */
int	ft_tolower(int c)
{
	if (!((c >= 'A') && (c <= 'Z')))
		return (c);
	return (c - 'A' + 'a');
}

int	ft_isspace(int c)
{
	return ((c == ' ') || (c == '\t')
		|| (c == '\n') || (c == '\v') || (c == '\f') || (c == '\r'));
}
