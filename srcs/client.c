/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 20:01:03 by agrumbac          #+#    #+#             */
/*   Updated: 2018/11/03 23:49:53 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

static const char	*cmd_str =
{
	[CMD_BAD] = "invalid command",
	[CMD_LS] = "ls ",//how about plain ls?
	[CMD_CD] = "cd ",
	[CMD_GET] = "get ",
	[CMD_PUT] = "put ",
	[CMD_PWD] = "pwd",
	[CMD_QUIT] = "quit"
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
**
*/

static enum e_cmd	determine_command(const char *command)
{
	return (CMD_BAD
	|	CMD_LS * !ft_strncmp(cmd_str[CMD_LS], command, 3)
	|	CMD_CD * !ft_strncmp(cmd_str[CMD_CD], command, 3)
	|	CMD_GET * !ft_strncmp(cmd_str[CMD_GET], command, 4)
	|	CMD_PUT * !ft_strncmp(cmd_str[CMD_PUT], command, 4)
	|	CMD_PWD * !ft_strncmp(cmd_str[CMD_PWD], command, 4)
	|	CMD_QUIT * !ft_strncmp(cmd_str[CMD_QUIT], command, 5));
}

static inline bool	cmd_put()
{
	struct stat		stat_buf;
	int				fd;

	if ((fd = open(filename, O_RDONLY)) < 0)
	{
		errors("Opening ", filename);
		return (false);
	}

	body = mmap(filename);
	header.body_size = fstat(filename);

	return (true);
}

static bool			smuggle_payload(int sock, const char *client_input)
{
	t_ftp_header	header;
	void			*body;

	header.cmd = determine_command(client_input);
	if (header.cmd == CMD_QUIT)
		return (false);

	if (header.cmd == CMD_LS || header.cmd == CMD_CD
	|| header.cmd == CMD_GET || header.cmd == CMD_PUT)
	{
		const char *filename = client_input + ft_strlen(cmd_str[header.cmd]);

		if (header.cmd == CMD_PUT)
		{
			if (cmd_put() == false)
				header = {CMD_BAD, 0};
		}
		else
		{
			body = filename;
			header.body_size = ft_strlen(body);
		}
	}
	else
		header.body_size = 0;

	send(sock, header, sizeof(header), 0);
	if (header.body_size != 0)
		send(sock, body, header.body_size, 0);
	return (true);
}

/*
**
*/

void			client_shell(int sock)
{
	char		client_input[FTP_CLIENT_MAX_INPUT];

	while (1)
	{
		if (prompt(&client_input) == 0 || \
			smuggle_payload(sock, &client_input) == false || \
			receive_answer() == false)
			break;
	}
	return ;
}

int				main(void/*int ac, char **av*/)
{
	int			sock;

	// parse_args();

	sock = socket_init("127.0.0.1", 4242, CLIENT);

	client_shell(sock);

	socket_cleanup();

	return (EXIT_SUCCESS);
}
