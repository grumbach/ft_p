/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_cmd_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 19:45:58 by agrumbac          #+#    #+#             */
/*   Updated: 2018/11/19 00:06:22 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

bool			cmd_cd(int sock, char *client_input)
{
	t_ftp_header	request;
	t_ftp_header	answer;
	size_t			body_size;
	int				ret;

	body_size = ft_strlen(client_input) + 1;
	if (body_size > MAXPATHLEN)
		body_size = MAXPATHLEN;

	request.type = CMD_CD;
	request.body_size = body_size;
	send(sock, &request, sizeof(request), 0);

	send(sock, client_input, body_size, 0);

	ret = recv(sock, &answer, sizeof(answer), 0);
	if (ret == 0)
		return (false);
	if (ret == -1)
	{
		warn("failed to recieve answer from server after cd");
		return (true);
	}

	if (answer.type == ASW_BAD)
		return (recieve_error(sock, answer.body_size));

	return (true);
}
