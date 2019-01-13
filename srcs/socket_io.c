/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket_io.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 16:04:44 by agrumbac          #+#    #+#             */
/*   Updated: 2019/01/13 20:21:27 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

bool		send_request(int sock, const int type, \
			const size_t body_size, const char *const body)
{
	t_ftp_header	request;

	request.type = type;
	request.body_size = body_size;
	if (send(sock, &request, sizeof(request), 0) == -1)
		return (false);
	if (body)
	{
		if (send(sock, body, body_size, 0) == -1)
			return (false);
	}
	return (true);
}

bool		send_answer(int sock, const int type, \
			const size_t body_size, const char *const body)
{
	return (send_request(sock, type, body_size, body));
}

static bool	receive_error(int sock, size_t message_len)
{
	char		buf[FTP_RECV_BUFFER];
	ssize_t		ret;

	ft_printf("\e[31m[SERVER ERROR] \e[0m");
	while (message_len > 0)
	{
		ret = recv(sock, buf, FTP_RECV_BUFFER, 0);
		if (ret == 0)
			return (false);
		if (ret == -1)
		{
			ft_printf("\n");
			warn("failed to receive error string");
			return (false);
		}
		ft_printf("%.*s", ret, buf);
		message_len -= ret;
	}
	ft_printf("\n");
	return (true);
}

bool		receive_answer(int sock, t_ftp_header *answer)
{
	ssize_t		ret;

	ret = recv(sock, answer, sizeof(*answer), 0);
	if (ret == 0)
		return (false);
	if (ret == -1)
	{
		answer->type = ASW_BAD;
		answer->body_size = 0;
		warn("failed to receive answer");
		return (false);
	}
	if (answer->type == ASW_BAD)
		return (receive_error(sock, answer->body_size));
	return (true);
}

bool		receive_file(int sock, const char *filename, size_t body_size)
{
	char		buf[FTP_RECV_BUFFER];
	int			fd;
	ssize_t		ret;

	if ((fd = open(filename, O_CREAT | O_WRONLY, 0700)) < 0)
	{
		warn("failed to open file for writing");
		return (true);
	}
	while (body_size > 0)
	{
		ret = recv(sock, buf, FTP_RECV_BUFFER, 0);
		if (ret == -1)
			warn("failed to receive file content");
		if (ret <= 0)
		{
			close(fd);
			return (false);
		}
		write(fd, buf, ret);
		body_size -= ret;
	}
	close(fd);
	return (true);
}
