/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 20:01:06 by agrumbac          #+#    #+#             */
/*   Updated: 2018/11/16 18:41:26 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"
#include <signal.h>


/*
** ft_p code
*/

static const	execute_command =
{
	CMD_BAD	 -> {send(CMD_BAD, error.len); send(error)}
	CMD_LS	 -> {fork() execve(ls) dup2() while(read(buf) send(size) send(buf))}
	CMD_MKDIR-> {mkdir(), send(OK)}
	CMD_CD	 -> {chdir() send(OK)}
	CMD_GET	 -> {open() fstat() mmap() send(file.size), send(file) munmap()}
	CMD_PUT	 -> {open(O_CREATE) write(file) send(OK)}
	CMD_PWD	 -> {cwd(), send(pwd)}
}

static int	receive_command(char *client_input)
{
	int ret = recv(client_input, FTP_CLIENT_MAX_INPUT);
	if (ret == -1)
		manage_error();

	return (ret);
}

static void		no_return_child_code(int client_sock)
{
	char			client_input[FTP_CLIENT_MAX_INPUT];

	while (receive_command(&client_input))
	{
		execute_command[cmd](client_input);
	}
	close(client_sock);
	exit(0);
}

/*
** exceptions
*/

void			signal_handler(__unused int sig)
{
	//TODO manage errors
	socket_cleanup();
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

		pid = fork();
		if (pid == 0)
			no_return_child_code(client_sock);
	}
}

int				main(int ac, char **av)
{
	int			sock;
	uint16_t	port

	if (parse_args(ac, av, NULL, &port) == false)
		return (EXIT_FAILURE);

	sock = socket_init(NULL, port, SERVER);

	signal(SIGINT, &signal_handler);

	accept_loop(sock);
}
