/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_checking.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 17:11:27 by agrumbac          #+#    #+#             */
/*   Updated: 2018/12/17 06:58:10 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

static bool	filename_invalid(const char *filename)
{
	size_t		len;

	len = ft_strlen(filename);
	if (len == 0)
		return (true);
	while (len)
	{
		len--;
		if (!ft_isprint(filename[len]))
			return (true);
	}
	return (false);
}

char		*get_filename_from(char *client_input)
{
	char		*filename;

	// path case
	filename = ft_strlaststr(client_input, "/");
	// filename case
	if (filename == NULL)
		filename = client_input;
	else
		filename += 1; // skip "/"

	if (filename_invalid(filename))
		return (NULL);
	return (filename);
}
