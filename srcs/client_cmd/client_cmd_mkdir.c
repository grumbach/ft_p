/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_cmd_mkdir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 19:47:12 by agrumbac          #+#    #+#             */
/*   Updated: 2018/11/22 17:14:16 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

bool			cmd_mkdir(int sock, char *client_input)
{
	t_ftp_header	answer;
	size_t			body_size;

	body_size = ft_strlen(client_input) + 1;
	if (body_size > MAXPATHLEN)
		body_size = MAXPATHLEN;

	send_request(sock, CMD_MKDIR, body_size);

	send(sock, client_input, body_size, 0);

	if (recieve_answer(sock, &answer) == false)
		return (false);

	return (true);

}
