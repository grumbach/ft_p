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
		tabl[j++][k] = 0;
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
			free(argv[i]);
			if (simple_path == NULL)
			{
				ft_del_tab(argv);
				return (NULL);
			}
			argv[i] = simple_path;
		}
		i++;
	}
	return (argv);
}

bool		cmd_recv(int sock, uint64_t body_size, char buf[MAXPATHLEN])
{
	int			ret;

	if (body_size > 0) // else ?
	{
		ret = recv(sock, buf, body_size, 0);
		if (ret != (int)body_size)
			return (false);
	}
	return (true);
}

void		send_full_answer(int sock, const int type, const ssize_t body_size, char *body)
{
	send_answer(sock, type, body_size); // return value ?
	if (send(sock, body, body_size, 0) != body_size)
		;// error on send request;
}


bool				recup_send_ls(int sock, int pipe_fds[2])
{
	ssize_t		read_nbr;
	char		buff[MAXPATHLEN];
	int			type;

	type = ASW_MORE;
	close(pipe_fds[1]);
	while ((read_nbr = read(pipe_fds[0], buff, MAXPATHLEN)) == MAXPATHLEN)
		send_full_answer(sock, type, read_nbr, buff);

	close(pipe_fds[0]);
	type = ASW_OK;
	if (read_nbr == -1)
	{
		send_answer(sock, type, 0);
		return (false);
	}
	send_full_answer(sock, type, read_nbr, buff);
	return (true);
}

#define BUFSIZE 128

typedef struct		s_smart_buff
{
	char	buff[BUFSIZE];
	int		size;
}					t_smart_buff;

void		send_ok(int sock, t_smart_buff *smart_buff)
{
	send_full_answer(sock, ASW_OK, smart_buff->size, smart_buff->buff);
}

int			ft_nbr_len(long nbr)
{
	int			i;

	i = 0;
	while (nbr)
	{
		i++;
		nbr /= 10;
	}
	return (i);
}

#include <dirent.h>

void		feel_smart_buff_one_elem(const char elem, t_smart_buff *smart_buff, int sock)
{
	if (smart_buff->size >= BUFSIZE)
	{
		send_full_answer(sock, ASW_MORE, smart_buff->size, smart_buff->buff);
		smart_buff->size = 0;
	}
	smart_buff->buff[smart_buff->size] = elem;
	smart_buff->size++;
}

void		feel_smart_buff(const char *data, t_smart_buff *smart_buff, int sock)
{
	int			i;

	i = 0;
	while (data[i])
	{
		feel_smart_buff_one_elem(data[i], smart_buff, sock);
		i++;
	}
	feel_smart_buff_one_elem('\n', smart_buff, sock);
}

bool		ft_ls_trait_file(const char *path, t_smart_buff *smart_buff, int sock)
{
	const char		*name;

	name = ft_strrchr(path, '/');
	if (!name)
		name = path;
	else
		name++;
	feel_smart_buff(name, smart_buff, sock);
	return (0);
}

int			ft_ls_trait_dir(const char *path, t_smart_buff *smart_buff, int sock)
{
	void			*dir;
	struct dirent	*dir_inside;

	if ((dir = opendir(path)) == NULL)
		return (0);
	while ((dir_inside = readdir(dir)))
	{
		feel_smart_buff(dir_inside->d_name, smart_buff, sock);
	}
	closedir(dir);
	return (0);
}


void		launch_ls_one_arg(t_smart_buff *smart_buff, const char *path, int sock)
{
	struct stat		buf;
	// t_ls_max_info	max_infos;

	if (lstat(path, &buf) == -1)
		return ;
	if (buf.st_mode & S_IFDIR)
		ft_ls_trait_dir(path, smart_buff, sock);
	else
		ft_ls_trait_file(path, smart_buff, sock);
	return ;
}

bool			launch_ls(char **argv_cmd, int sock)
{
	t_smart_buff	smart_buff;
	int				i;

	smart_buff.size = 0;
	if (!argv_cmd || !argv_cmd[0]) // utile ??
		return (false);
	i = 1;
	if (!argv_cmd[i])
	{
		char *name = simplify_path("/");
		launch_ls_one_arg(&smart_buff, name, sock);
		free(name);
	}
	else
		while (argv_cmd[i])
		{
			launch_ls_one_arg(&smart_buff, argv_cmd[i], sock);
			i++;
		}
	ft_del_tab(argv_cmd);
	send_ok(sock, &smart_buff);
	return (true);
}

bool			cmd_ls(int sock, uint64_t body_size)
{
	char			buf[MAXPATHLEN + 1];
	bool			ret;
	char			**argv_cmd;

	if (body_size > MAXPATHLEN)
		return (cmd_bad(sock, ERR_PATHLEN_OVERFLOW));

	if (cmd_recv(sock, body_size, buf) == false)
		return (false); // pourquoi juste false

	if ((argv_cmd = get_argv_cmd(buf)) == NULL)
		return (cmd_bad(sock, ERR_PATHLEN_OVERFLOW));

	if ((ret = launch_ls(argv_cmd, sock)) == false)
		return (cmd_bad(sock, ERR_PATHLEN_OVERFLOW));

	return (ret);
}
//{fork() execve(ls) dup2() while(read(buf) send(size) send(buf))}
