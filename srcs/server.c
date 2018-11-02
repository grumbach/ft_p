/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 20:01:06 by agrumbac          #+#    #+#             */
/*   Updated: 2018/11/02 22:44:47 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"
//
// /*
// ** ft_p code
// */
//
// static void		child_code()
// {
// 	//TODO ft_p happens here
// }
//
// /*
// ** exceptions
// */
//
// void			signal_handler(int sig)
// {
// 	//TODO manage errors
// 	socket_cleanup();
// 	exit(0);
// }

/*
** main code
*/

static void		accept_loop(int sock)
{
	struct sockaddr_in		client;
	int						client_sock;
	socklen_t				socklen;

	while (1)
	{
		socklen = sizeof(struct sockaddr_in);
		client_sock = accept(sock, (struct sockaddr *)&client, \
			(socklen_t*)&socklen);

		if (client_sock == -1)
			fatal("Error while attempting to accept connection");

		write(client_sock, "SUCESS\n", 8);

		// pid = fork();
		// if (pid == 0) //if child
		// 	child_code();

		//father stays in the loop
	}
}

int				main(void/*int ac, char **av*/)
{
	int			sock;

	// parse_args();

	sock = socket_init(NULL, 4242, SERVER);

	// signal(0 /* what is sig? */, &signal_handler);

	accept_loop(sock);
}
