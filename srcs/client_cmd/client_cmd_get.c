/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_cmd_get.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 19:46:59 by agrumbac          #+#    #+#             */
/*   Updated: 2019/01/12 16:37:03 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

__attribute__((warn_unused_result))
bool			cmd_get(int sock, char *client_input)
{
	t_ftp_header	answer;
	size_t			body_size;
	char			*filename;

	body_size = ft_strlen(client_input) + 1;

	filename = get_filename_from(client_input);
	if (filename == NULL)
	{
		warn("invalid filename");
		return (true);
	}
	send_request(sock, CMD_GET, body_size);
	send(sock, client_input, body_size, 0);

	if (receive_answer(sock, &answer) == false)
		return (false);

	if (answer.type == ASW_OK)
		return (receive_file(sock, filename, answer.body_size));
	return (true);
}
