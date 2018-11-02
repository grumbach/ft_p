/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 20:01:06 by agrumbac          #+#    #+#             */
/*   Updated: 2018/11/02 23:20:33 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"
#include <signal.h>


/*
** ft_p code
*/

static void		no_return_child_code(int client_sock)
{
	//TODO ft_p happens here
	send(client_sock , "CHILD server says hello\n", 24, 0);
}

/*
** exceptions
*/

void			signal_handler(__unused int sig)
{
	//TODO manage errors
	// socket_cleanup(??);
	ft_puts("Exiting...");
	exit(0);
}

/*
** main code
*/

static void		accept_loop(int sock)
{
	struct sockaddr_in		client;
	int						client_sock;
	socklen_t				socklen;
	pid_t					pid;

	while (1)
	{
		socklen = sizeof(struct sockaddr_in);
		client_sock = accept(sock, (struct sockaddr *)&client, \
			(socklen_t*)&socklen);

		if (client_sock == -1)
			fatal("Error while attempting to accept connection");

		send(client_sock , "SUCESS\n", 8, 0);
		pid = fork();
		if (pid == 0)
			no_return_child_code(client_sock);
	}
}

int				main(void/*int ac, char **av*/)
{
	int			sock;

	// parse_args();

	sock = socket_init(NULL, 4242, SERVER);

	signal(SIGINT, &signal_handler);

	accept_loop(sock);
}
