/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 20:01:03 by agrumbac          #+#    #+#             */
/*   Updated: 2018/11/02 22:44:41 by agrumbac         ###   ########.fr       */
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

	char buf[9];
	read(sock, buf, 8);
	ft_puts(buf);

	socket_cleanup(sock);

	return (EXIT_SUCCESS);
}
