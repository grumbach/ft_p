/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 20:01:06 by agrumbac          #+#    #+#             */
/*   Updated: 2019/01/13 23:41:36 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include <signal.h>

/*
** exceptions
*/

void			signal_handler(int sig)
{
	(void)sig;
	socket_cleanup();
	ft_puts("\n"FTP_LOG"Exiting...");
	exit(EXIT_SUCCESS);
}

/*
** Forking server
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
			fatal("while attempting to accept connection");
		pid = fork();
		if (pid == -1)
			fatal("while attempting to fork a new server");
		if (pid == 0)
			no_return_child_code(client_sock);
		waitpid(-1, (int[1]){1}, WNOHANG);
	}
}

int				main(int ac, char **av)
{
	int			sock;
	uint16_t	port;

	if (parse_args(ac, av, NULL, &port) == false)
		return (EXIT_FAILURE);
	set_root_path();
	sock = socket_init(NULL, port, SERVER);
	signal(SIGINT, &signal_handler);
	accept_loop(sock);
}
