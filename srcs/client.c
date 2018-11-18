/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 20:01:03 by agrumbac          #+#    #+#             */
/*   Updated: 2018/11/18 19:21:40 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

/*
** Client actions
*/

static bool	(*execute_command[CMD_LAST])(int, char*) =
{
	// CMD_BAD	 -> {send nothing; disp error}
	// CMD_LS	 -> {       send(args.len);  send(args)}
	// CMD_MKDIR-> {       send(args.len);  send(args)}
	// CMD_CD	 -> {       send(args.len);  send(args)}
	// CMD_GET	 -> {       send(args.len);  send(args)}
	// CMD_PUT	 -> {mmap() send(file.size); send(file) munmap()}
	// CMD_PWD	 -> {       send() len==0}
	// CMD_QUIT -> {say_bye()}
};

static int	prompt(char *client_input)
{
	int		read_chars;

	ft_printf("[ft_p]$> ");

	read_chars = read(0, client_input, FTP_CLIENT_MAX_INPUT - 1);
	if (read_chars == -1)
		fatal("Failed to read on stdin");
	client_input[read_chars] = '\0';

	return (read_chars);
}

/*
** Client main loop
*/

void			client_shell(int sock)
{
	char			client_input[FTP_CLIENT_MAX_INPUT];
	enum e_cmd		cmd;

	while (1)
	{
		prompt(client_input);
		cmd = determine_command(client_input);
		execute_command[cmd](sock, client_input);
		if (cmd == CMD_QUIT)
			break ;
	}
	return ;
}

int				main(__unused int ac, __unused char **av)
{
	int				sock;
	char			*address;
	uint16_t		port;

	if (parse_args(ac, av, &address, &port) == false)
		return (EXIT_FAILURE);

	sock = socket_init(address, port, CLIENT);

	client_shell(sock);

	socket_cleanup();

	return (EXIT_SUCCESS);
}
