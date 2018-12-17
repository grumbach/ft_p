/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_cmd_get.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 19:46:59 by agrumbac          #+#    #+#             */
/*   Updated: 2018/12/06 07:24:02 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static bool		recieve_file(int sock, const char *filename, size_t body_size)
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
			warn("failed to recieve file content form server");
			return (true);
		}
		write(fd, buf, ret);
		body_size -= ret;
	}
	close(fd);
	return (true);
}

static char		*get_filename_from(char *client_input)
{
	char		*filename;

	//last slash in client_input
	filename = ft_strlaststr(client_input, "/");
	//if not client_input
	if (filename == NULL)
	{
		filename = ft_strstr(client_input, "get");
		if (filename == NULL)
			return (NULL);
		filename += 3; // skip "get"
	}
	else
		filename += 1; // skip "/"

	if (filename_invalid(filename))
		return (NULL);
	return (filename);
}

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
