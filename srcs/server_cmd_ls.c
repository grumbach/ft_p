/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_cmd_ls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 19:45:19 by agrumbac          #+#    #+#             */
/*   Updated: 2018/11/18 19:54:15 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

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

void			ft_del_tab(char **tabl)
{
	int				i;

	i = 0;
	if (tabl)
		while (tabl[i])
		{
			free(tabl[i]);
			i++;
		}
	free(tabl);
}

static size_t		ft_st(char *s, char c)
{
	char	*i;
	size_t	x;

	i = s;
	x = 0;
	while (*i)
	{
		++x;
		while (*i == c)
			++i;
		while (*i != c && *i)
			++i;
	}
	return (x);
}

char				**ft_strsplit(char *str, char c)
{
	size_t			i;
	char			**tabl;
	size_t			j;
	size_t			k;

	if (!str || c == 0
		|| !(tabl = ft_memalloc(sizeof(char *) * (ft_st(str, c) + 1))))
		return (NULL);
	j = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] == c)
			i++;
		k = 0;
		while (str[(i + k)] && str[(i + k)] != c)
			++k;
		if (k == 0 || (tabl[j] = ft_strsub(str, (unsigned int)(i), k)) == NULL)
			break ;
		tabl[j++][k + 1] = 0;
		i = i + k;
	}
	tabl[j] = NULL;
	return (tabl);
}

// pwd_server = where am i

char		**get_argv_cmd(char *input)
{
	char		*simple_path;
	char		**argv;
	int			i;

	argv = ft_strsplit(input, ' '); // super parser de la mort qui tue
	i = 0;
	while (argv[i])
	{
		if (ft_str_as_slash(argv[i]) == true)
		{
			simple_path = simplify_path(argv[i]);
			if (simple_path == NULL)
			{
				ft_del_tab(argv);
				return (NULL);
			}
			argv[i] = simple_path;
		}
	}
	return (argv);
}

bool		cmd_recv(int sock, uint64_t body_size, char buf[MAXPATHLEN])
{
	int			ret;

	if (body_size > 0) // else ?
	{
		ret = recv(sock, buf, body_size, 0);
		if (ret != body_size)
			return (false);
	}
	return (true);
}

int		wait_son(pid_t pid_son)
{
	struct rusage		usage;
	int					son_return;
	pid_t				pid_return;

	pid_return = wait4(pid_son, &son_return, WUNTRACED, &usage);
	if (pid_return == -1)
		return (pid_return);
	return (son_return);
}

pid_t			fork_and_launch_ls(char **argv_cmd, int pipe_fds[2])
{
	pid_t pid_son;

	pid_son = -1;
	if (ft_strcmp(argv_cmd[0], "ls") == 0)
	{
		close(STDIN_FILENO);
		pid_son = fork();

		if (!pid_son)
		{
			close(pipe_fds[1]);
			dup2(pipe_fds[0], STDERR_FILENO);
			dup2(pipe_fds[0], STDOUT_FILENO);
			execve(argv_cmd[0], argv_cmd, NULL); // env ??
			ft_putendl_fd("Error: execve error", 2);
			exit(1);
		}
	}
	ft_del_tab(argv_cmd);
	return (pid_son);
}

void		send_full_answer(int sock, const int type, const size_t body_size, char *body)
{
	send_answer(sock, type, body_size); // return value ?
	if (send(sock, body, body_size, 0) != body_size)
		;// error on send request;
}


bool				recup_send_ls(int sock, int pipe_fds[2])
{
	size_t		read_nbr;
	char		buff[MAXPATHLEN];
	int			type;

	type = ASW_MORE;
	close(pipe_fds[0]);
	while ((read_nbr = read(pipe_fds[1], buff, MAXPATHLEN)) == MAXPATHLEN)
		send_full_answer(sock, type, read_nbr, buff);
	close(pipe_fds[1]);
	type = ASW_OK;
	if (read_nbr == -1)
	{
		send_answer(sock, type, 0);
		return (false);
	}
	send_full_answer(sock, type, read_nbr, buff);
	return (true);
}

bool			cmd_ls(int sock, uint64_t body_size)
{
	char			buf[MAXPATHLEN + 1];
	pid_t			pid_son;
	ssize_t			ret;
	char			*path;
	char			**argv_cmd;
	int				pipe_fds[2];

	if (body_size > MAXPATHLEN)
		return (cmd_bad(sock, ERR_PATHLEN_OVERFLOW));

	if (cmd_recv(sock, body_size, buf) == false)
		return (false);

	if (pipe(pipe_fds) == -1)
		return (cmd_bad(sock, ERR_PATHLEN_OVERFLOW));

	if ((argv_cmd = get_argv_cmd(buf)) == NULL)
		return (cmd_bad(sock, ERR_PATHLEN_OVERFLOW));

	if ((pid_son = fork_and_launch_ls(argv_cmd, pipe_fds)) == -1)
		return (cmd_bad(sock, ERR_PATHLEN_OVERFLOW));

	if (wait_son(pid_son))
		return (cmd_bad(sock, ERR_PATHLEN_OVERFLOW));

	ret = recup_send_ls(sock, pipe_fds);

	ft_printf("cmd_ls");
	return (ret);
}
//{fork() execve(ls) dup2() while(read(buf) send(size) send(buf))}
