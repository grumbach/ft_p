/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 20:01:03 by agrumbac          #+#    #+#             */
/*   Updated: 2018/11/16 18:39:55 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

static const char	*cmd_str =
{
	[CMD_BAD] = "invalid command",
	[CMD_LS] = "ls ",//how about plain ls?
	[CMD_MKDIR] = "mkdir ",
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
**
*/

static enum e_cmd	determine_command(const char *command)
{
	return (CMD_BAD
	|	CMD_LS * !ft_strncmp(cmd_str[CMD_LS], command, 3)
	|	CMD_MKDIR * !ft_strncmp(cmd_str[CMD_MKDIR], command, 6)
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

static const execute_command =
{
	CMD_BAD	 -> {send nothing; disp error}
	CMD_LS	 -> {       send(args.len);  send(args)}
	CMD_MKDIR-> {       send(args.len);  send(args)}
	CMD_CD	 -> {       send(args.len);  send(args)}
	CMD_GET	 -> {       send(args.len);  send(args)}
	CMD_PUT	 -> {mmap() send(file.size); send(file) munmap()}
	CMD_PWD	 -> {       send() len==0}
	CMD_QUIT -> {say_bye()}
}

/*
**
*/

void			client_shell(int sock)
{
	char			client_input[FTP_CLIENT_MAX_INPUT];
	enum e_cmd		cmd;

	while (1)
	{
		prompt(&client_input);
		cmd = determine_command(client_input);
		execute_command[cmd](client_input);
		if (cmd == CMD_QUIT)
			break ;
	}
	return ;
}

int				main(int ac, char **av)
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
