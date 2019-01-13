/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 07:28:07 by agrumbac          #+#    #+#             */
/*   Updated: 2018/04/19 07:30:55 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Calculates string length up to n
*/

#include "libft.h"

size_t		ft_strnlen(const char *s, const size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && s[i])
		i++;
	return (i);
}
