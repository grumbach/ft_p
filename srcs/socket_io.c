/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket_io.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 16:04:44 by agrumbac          #+#    #+#             */
/*   Updated: 2018/11/20 18:43:22 by agrumbac         ###   ########.fr       */
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

bool		recieve_error(int sock, size_t message_len)
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
			warn("failed to recieve error string form server");
			return (true);
		}

		ft_printf("%.*s", ret, buf);
		message_len -= ret;
	}
	ft_printf("\n");
	return (true);
}

bool		recieve_answer(int sock, t_ftp_header *answer)
{
	ssize_t		ret;

	ret = recv(sock, answer, sizeof(*answer), 0);
	if (ret == 0)
		return (false);
	if (ret == -1)
	{
		answer->type = ASW_BAD;
		answer->body_size = 0;
		warn("failed to recieve answer from server");//NB from server?
		return (true);
	}

	if (answer->type == ASW_BAD)
		return (recieve_error(sock, answer->body_size));
	return (true);
}
