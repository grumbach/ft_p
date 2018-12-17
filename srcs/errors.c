/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/03 17:38:53 by agrumbac          #+#    #+#             */
/*   Updated: 2018/11/20 19:14:59 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

void			fatal(const char *error)
{
	ft_perr(FTP_FATAL);
	ft_perr(error);
	ft_perr("\n");
	exit(EXIT_FAILURE);
}

void			warn(const char *warning)
{
	ft_printf("%s%s\n", FTP_WARN, warning);
}

bool			parse_args(int ac, char **av, char **address, uint16_t *port)
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
