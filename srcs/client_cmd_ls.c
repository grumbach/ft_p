/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_cmd_ls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 19:47:09 by agrumbac          #+#    #+#             */
/*   Updated: 2018/11/18 19:54:44 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

bool		recieve_body(int sock, t_ftp_header answer, char body[MAXPATHLEN + 1])
{
	int		ret;

	if (answer.body_size == 0)
		return (true);

	if (answer.body_size > MAXPATHLEN)
		return (false);

	ret = recv(sock, body, answer.body_size, 0);

	if (ret == 0)
		return (false);
	if (ret == -1)
	{
		warn("failed to recieve answer body from server");//NB from server?
		return (true);
	}

	return (true);
}

bool				recieve_cmd(int sock)
{
	char				body[MAXPATHLEN + 1];
	t_ftp_header		answer;

	while (1)
	{
		if (recieve_answer(sock, &answer) == false) // a changer <= boucle
			return (false);
		if (answer.type == ASW_OK || answer.type == ASW_MORE)
		{
			recieve_body(sock, answer, body);
			body[answer.body_size] = 0;
			printf("%*s", (int)answer.body_size, body);
		}
		if (answer.type != ASW_MORE)
			break ;
	}
	return (true);
}

bool			cmd_ls(int sock, char *client_input)
{
	size_t			body_size;

	body_size = ft_strlen(client_input) + 1;
	if (body_size > MAXPATHLEN)
		body_size = MAXPATHLEN;

	send_request(sock, CMD_LS, body_size);

	send(sock, client_input, body_size, 0);
	recieve_cmd(sock);

	return (true);
}
//{       send(args.len);  send(args)}
