/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 20:01:03 by agrumbac          #+#    #+#             */
/*   Updated: 2018/11/20 19:54:37 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

/*
** Client actions
*/

static bool	(*execute_command[CMD_LAST])(int, char*) =
{
	[CMD_BAD] = &cmd_bad,
	[CMD_LS] = &cmd_ls,
	[CMD_MKDIR] = &cmd_mkdir,
	[CMD_CD] = &cmd_cd,
	[CMD_GET] = &cmd_get,
	[CMD_PUT] = &cmd_put,
	[CMD_PWD] = &cmd_pwd,
	[CMD_QUIT] = &cmd_quit
};

static int	prompt(char *client_input)
{
	int		read_chars;

	ft_printf("\e[34m[\e[32mft_p\e[34m]$> \e[0m");

	read_chars = read(0, client_input, FTP_CLIENT_MAX_INPUT - 1);
	if (read_chars < 0)
		fatal("Failed to read on stdin");
	if (read_chars == 0)
		return (0);

	client_input[read_chars - 1] = '\0'; //remove '\n'
	return (read_chars);
}

int		client_ls()
{
	CMD_LS	 -> {       send(args.len);  send(args)}

	;
}

int		client_cd()
{
	CMD_CD	 -> {       send(args.len);  send(args)}

	;
}

int		client_bad()
{
	CMD_BAD	 -> {send nothing; disp error}
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
		if (prompt(client_input) == 0)
			break ;
		cmd = determine_command(client_input);
		execute_command[cmd](sock, client_input);
		if (cmd == CMD_QUIT)
			break ;
	}
	ft_printf("\e[32mExiting...\n\e[0m");
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
