/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_cmd_ls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 19:47:09 by agrumbac          #+#    #+#             */
/*   Updated: 2019/01/12 16:36:59 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

__attribute__((warn_unused_result))
static bool		receive_body(int sock, t_ftp_header answer, char *body)
{
	int		ret;

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
		return (true);
	}

	return (true);
}

__attribute__((warn_unused_result))
bool			cmd_ls(int sock, char *client_input)
{
	size_t			body_size;

	body_size = ft_strlen(client_input) + 1;

	send_request(sock, CMD_LS, body_size);
	send(sock, client_input, body_size, 0);

	char				body[MAXPATHLEN + 1];
	t_ftp_header		answer;

	answer.type = ASW_MORE;
	while (answer.type == ASW_MORE)
	{
		if (receive_answer(sock, &answer) == false) // a changer <= boucle
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
