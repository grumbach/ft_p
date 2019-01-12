/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket_io.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 16:04:44 by agrumbac          #+#    #+#             */
/*   Updated: 2019/01/12 16:38:38 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

void		send_request(int sock, const int type, const size_t body_size)
{
	t_ftp_header	request;

	request.type = type;
	request.body_size = body_size;
	send(sock, &request, sizeof(request), 0);
}

void		send_answer(int sock, const int type, const size_t body_size)
{
	send_request(sock, type, body_size);
}

void		send_full_answer(int sock, const int type, char *body, const ssize_t body_size)
{
	send_answer(sock, type, body_size);
	send(sock, body, body_size, 0);
}

__attribute__((warn_unused_result))
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
			warn("failed to receive error string form server");
			return (true);
		}

		ft_printf("%.*s", ret, buf);
		message_len -= ret;
	}
	ft_printf("\n");
	return (true);
}

__attribute__((warn_unused_result))
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
		warn("failed to receive answer from server");//NB from server?
		return (true);
	}

	if (answer->type == ASW_BAD)
		return (receive_error(sock, answer->body_size));
	return (true);
}

__attribute__((warn_unused_result))
bool		receive_file(int sock, const char *filename, size_t body_size)
{
	char		buf[FTP_RECV_BUFFER];
	int			fd;
	ssize_t		ret;

	fd = open(filename, O_CREAT | O_WRONLY);
	if (fd < 0)
	{
		warn("failed to open file for writing");
		return (true);
	}
	while (body_size > 0)
	{
		ret = recv(sock, buf, FTP_RECV_BUFFER, 0);
		if (ret == 0)
		{
			close(fd);
			return (false);
		}
		if (ret == -1)
		{
			close(fd);
			warn("failed to receive file content form server");
			return (true);
		}
		write(fd, buf, ret);
		body_size -= ret;
	}
	close(fd);
	return (true);
}
