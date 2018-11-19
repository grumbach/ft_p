/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_ls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 03:45:20 by gnebie            #+#    #+#             */
/*   Updated: 2018/11/19 03:45:21 by gnebie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

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

char				**ft_strsplit(char *s, char c)
{
	char	*i;
	char	**a;
	size_t	j;
	size_t	k;

	if (!s || !(a = ft_memalloc(sizeof(char *) * (ft_st((char *)s, c) + 1))))
		return (NULL);
	j = 0;
	i = (char *)s;
	while (*i)
	{
		while (*i == c && *i)
			i++;
		if (!(*i))
			break ;
		k = 0;
		while (*(i + k) && *(i + k) != c)
			++k;
		if ((a[j] = ft_strsub(s, (unsigned int)(i - s), k)) == NULL)
			return (NULL);
		a[j++][k + 1] = 0;
		i = i + k;
	}
	a[j] = 0;
	return (a);
}

// pwd_server = where am i

char		*get_argv_cmd(char *input)
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

bool		send_ls()
{
	while ((buff_size = read(buf)) != -1)
	{
		send(buff_size);
		send(buf);
		if (buff_size != BUFF_SIZE)
			return (true);
	}
	return (false);
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
		dup2(STDOUT_FILENO, STDIN_FILENO);
		execve(argv_cmd[0], argv_cmd);
		ft_putendl_fd("Error: execve error", 2);
		exit(1);
	}
	if (pid_son == -1)
		return (server_error());
	struct		rusage usage;
	int			son_return;
	pid_t		pid_return;
	pid_return = wait4(pid_son, &son_return, WUNTRACED, usage);
	int		ret;
	ret = send_ls();
	return (ret);
}
