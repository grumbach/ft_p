/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket_io.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 16:04:44 by agrumbac          #+#    #+#             */
/*   Updated: 2019/01/13 23:43:22 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

static bool	send_body(int sock, size_t body_size, const char *const body)
{
	ssize_t	ret;
	size_t	offset;

	offset = 0;
	while (body_size > 0)
	{
		ret = body_size;
		if (body_size > FTP_SEND_BUFFER)
			ret = FTP_SEND_BUFFER;
		ret = send(sock, body + offset, ret, 0);
		if (ret == -1)
			return (false);
		body_size -= ret;
		offset += ret;
	}
	return (true);
}

bool		send_request(int sock, const int type, \
			const size_t body_size, const char *const body)
{
	t_ftp_header	request;

	request.type = type;
	request.body_size = body_size;
	if (send(sock, &request, sizeof(request), 0) == -1)
	{
		warn("send failed while sending request");
		return (false);
	}
	if (body)
	{
		if (send_body(sock, body_size, body) == false)
		{
			warn("send failed while sending body");
			return (false);
		}
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
