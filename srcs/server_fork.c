/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_fork.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 18:08:35 by agrumbac          #+#    #+#             */
/*   Updated: 2018/11/18 20:47:48 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

/*
** Actual ft_p code from forked server
*/

static bool	(*execute_command[CMD_LAST])(int, uint64_t) =
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
	int		ret;

	ret = recv(sock, request, sizeof(*request), 0);

	if (ret == 0)
	{
		ft_printf("[LOG] connection closed on socket {%d}\n", sock);
		return (false);
	}
	else if (ret != sizeof(*request))
	{
		ft_printf("[ERROR] receiving on socket {%d} ret: %d request: %d\n", sock, ret, sizeof(*request));
		return (false);
	}
	return (true);
}

void		no_return_child_code(int sock)
{
	t_ftp_header	request;

	ft_printf("[LOG] begin connection on socket {%d}\n", sock);

	while (receive_command(sock, &request))
	{
		if (request.type >= CMD_QUIT)
		{
			request.type = CMD_BAD;
			request.body_size = ERR_BAD_CMD_CODE;
		}

		ft_printf("[LOG] begin connection on socket {%d} CMD {%d} %d\n", sock, request.type, CMD_BAD);
		execute_command[request.type + 1](sock, request.body_size);

	}

	ft_printf("[LOG] closing socket {%d}\n", sock);
	close(sock);
	exit(0);
}
