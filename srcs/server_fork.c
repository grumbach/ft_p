/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_fork.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 18:08:35 by agrumbac          #+#    #+#             */
/*   Updated: 2019/01/13 19:11:49 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

/*
** Actual ft_p code from forked server
*/

static bool	(*g_execute_command[])(int, uint64_t) =
{
	[CMD_BAD] = &cmd_bad,
	[CMD_LS] = &cmd_ls,
	[CMD_MKDIR] = &cmd_mkdir,
	[CMD_CD] = &cmd_cd,
	[CMD_GET] = &cmd_get,
	[CMD_PUT] = &cmd_put,
	[CMD_PWD] = &cmd_pwd
};

static bool	receive_command(int sock, t_ftp_header *request)
{
	ssize_t		ret;

	ret = recv(sock, request, sizeof(*request), 0);
	if (ret == 0)
	{
		ft_printf(FTP_LOG "\t\t{%d}\tconnection closed on socket\n", sock);
		return (false);
	}
	else if (ret != sizeof(*request))
	{
		ft_printf(FTP_WARN "\t{%d}\tbad request from socket\n", sock);
		return (false);
	}
	return (true);
}

void		no_return_child_code(int sock)
{
	t_ftp_header	request;

	ft_printf(FTP_LOG "\t\t{%d}\tbegin connection on socket\n", sock);
	while (receive_command(sock, &request))
	{
		if (request.type >= CMD_QUIT || request.type == CMD_BAD)
		{
			request.type = CMD_BAD;
			request.body_size = ERR_BAD_CMD_CODE;
		}
		ft_printf(FTP_LOG "\t\t{%d}\treceived command %d\n", sock, \
			request.type);
		if (!g_execute_command[request.type](sock, request.body_size))
			break ;
	}
	ft_printf(FTP_LOG "\t\t{%d}\tclosing socket\n", sock);
	if (close(sock) == -1)
		warn("failed closing socket");
	exit(EXIT_SUCCESS);
}
