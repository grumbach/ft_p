/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 20:01:03 by agrumbac          #+#    #+#             */
/*   Updated: 2018/11/02 23:05:11 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

# define FTP_QUIT			42

// int			pseudo_shell()
// {
// 	prompt();
// 	send();
// 	recv();
// 	print();
// }
//
// void		client_code()
// {
// 	//TODO ft_p happens here
// 	while (1)
// 	{
// 		if (pseudo_shell() == FTP_QUIT)
// 			break;
// 	}
// 	return ;
// }

int			main(void/*int ac, char **av*/)
{
	int		sock;

	// parse_args();

	sock = socket_init("127.0.0.1", 4242, CLIENT);

	// client_code();

	while (1)
	{
		char buf[9];
		if (recv(sock, buf, 8, 0) == 0)
			break;
		ft_puts(buf);
	}
	ft_puts("server disconnected...");

	socket_cleanup(sock);

	return (EXIT_SUCCESS);
}
