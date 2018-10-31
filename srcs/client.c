/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 20:01:03 by agrumbac          #+#    #+#             */
/*   Updated: 2018/10/31 20:19:36 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

void		client_code()
{
	//TODO ft_p happens here
}

int			main(int ac, char **av)
{
	parse_args();

	server_init();

	client_code();

	server_cleanup();

	return (EXIT_SUCCESS);
}
