/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_cmd_ls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 19:47:09 by agrumbac          #+#    #+#             */
/*   Updated: 2019/01/13 17:24:08 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

__attribute__((warn_unused_result))
static bool		receive_body(int sock, t_ftp_header answer, char *body)
{
	ssize_t		ret;

	if (answer.body_size > MAXPATHLEN)
	{
		warn("invalid answer from server");
		return (true);
	}

	ret = recv(sock, body, answer.body_size, 0);
	if (ret == 0)
		return (false);
	if (ret == -1)
	{
		warn("failed to receive answer body from server");
		return (false);
	}

	return (true);
}

__attribute__((warn_unused_result))
bool			cmd_ls(int sock, char *client_input)
{
	char				body[MAXPATHLEN + 1];
	size_t				body_size;
	t_ftp_header		answer;

	body_size = ft_strlen(client_input) + 1;

	if (send_request(sock, CMD_LS, body_size, client_input) == false)
		return (false);

	answer.type = ASW_MORE;
	while (answer.type == ASW_MORE)
	{
		if (receive_answer(sock, &answer) == false)
			return (false);
		if (answer.type == ASW_OK || answer.type == ASW_MORE)
		{
			if (receive_body(sock, answer, body) == false)
				return (false);
			write(1, body, answer.body_size);
		}
	}
	return (true);
}
