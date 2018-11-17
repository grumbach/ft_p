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

bool		ft_str_as_slash(char *str)
{
	while(*str)
	{
		if (*str == '/')
			return (true);
		str++;
	}
	return (false);
}

// pwd_server = where am i

char		*get_real_path(char *path)
{
	char		*new_path;

	if (path[0] == '/')
		new_path = path;
	else
	{
		new_path = ft_strjoin(pwd_server, path);
		free(path);
	}
	return (new_path);
}

char		**remove_path_returns(char **path_tab)
{
	int			i;

	i = 0;
	while (path_tab[i])
	{
		if (!ft_strcmp(path_tab[i], ".."))
		{
			if (i > 0)
				remove_prev(path_tab, i);
			remove_elem(path_tab, i);
		}
		else if (!ft_strcmp(path_tab[i], "."))
		{
			remove_elem(path_tab, i);
		}
		else
			i++;
	}
}

char		*simplify_path(char *path)
{
	char		**path_tab;

	path = get_real_path(path);
	path_tab = ft_strsplit(path, '/');// faire des vrai fonction de tableau ? ou des fonctions de liste chainées
	free(path);
	if (path_tab == NULL)
		return (NULL)
	path_tab = remove_path_returns(path_tab);
	path = ft_concat_array(path_tab);
	path = add_root(path);
	return (path);
}

char		*get_argv_cmd(char *input)
{
	char		*simple_path;
	char		*new_path;
	char		**argv;
	int			i;

	argv = ft_strsplit(input);
	i = 0;
	while (argv[i])
	{
		if (ft_str_as_slash(argv[i]) == true)
		{
			simple_path = simplify_path(argv[i]);
			if (simple_path == NULL)
			{
				ft_deltab(argv);
				return (NULL);
			}
			argv[i] = simple_path;
		}
	}
	return (argv);
}

int		server_error()
{
	;
}

int		server_ls()
{
	char		**argv_cmd;
	int			pid_son;

	if ((argv_cmd = get_argv_cmd()) == NULL)
		return (server_error());

	pid_son = fork();
	if (!pid_son)
	{
		dup2();
		execve("ls", argv_cmd);
		ft_putendl_fd("Error: execve error", 2);
		exit(1);
	}
	while ((buff_size = read(buf)) != -1)
	{
		send(buff_size);
		send(buf);
		if (buff_size != BUFF_SIZE)
			return (true);
	}
	rturn (false);
}

int		server_cd()
{
	chdir()
	send(OK)
}

int		server_bad()
{
	send(CMD_BAD, error.len);
	send(error);
}


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
