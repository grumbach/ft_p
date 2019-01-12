/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_checking.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 17:11:27 by agrumbac          #+#    #+#             */
/*   Updated: 2019/01/12 16:39:17 by agrumbac         ###   ########.fr       */
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

bool		parse_args(int ac, char **av, char **address, uint16_t *port)
{
	// client case
	if (address && ac == 3)
	{
		*address = av[1];
		*port = (uint16_t)ft_atoi(av[2]);
		return (true);
	}
	//server case
	else if (address == NULL && ac == 2)
	{
		*port = (uint16_t)ft_atoi(av[1]);
		return (true);
	}
	// error case
	ft_printf("usage : %s %s<port>\n", av[0], address ? "<address> " : "");
	return (false);
}
