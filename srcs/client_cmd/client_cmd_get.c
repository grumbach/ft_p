/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_cmd_get.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 19:46:59 by agrumbac          #+#    #+#             */
/*   Updated: 2018/12/17 06:51:08 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

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

	if (recieve_answer(sock, &answer) == false)
		return (false);

	if (answer.type == ASW_OK)
		return (recieve_file(sock, filename, answer.body_size));
	return (true);
}