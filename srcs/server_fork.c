/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_fork.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 18:08:35 by agrumbac          #+#    #+#             */
/*   Updated: 2018/11/18 18:53:53 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

/*
** Actual ft_p code from forked server
*/

static bool	(*execute_command[CMD_LAST])(int, uint64_t) =
{
	// CMD_BAD	 -> {send(CMD_BAD, error.len); send(error)}
	// CMD_LS	 -> {fork() execve(ls) dup2() while(read(buf) send(size) send(buf))}
	// CMD_MKDIR-> {mkdir(), send(OK)}
	// CMD_CD	 -> {chdir() send(OK)}
	// CMD_GET	 -> {open() fstat() mmap() send(file.size), send(file) munmap()}
	// CMD_PUT	 -> {open(O_CREATE) write(file) send(OK)}
	// CMD_PWD	 -> {cwd(), send(pwd)}
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
		ft_printf("[ERROR] receiving on socket {%d}\n", sock);
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
			request.type = CMD_BAD;

		ft_printf("[LOG] begin connection on socket {%d}\n", sock);
		execute_command[request.type](sock, request.body_size);
	}

	ft_printf("[LOG] closing socket {%d}\n", sock);
	close(sock);
	exit(0);
}
