/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_cmd_get.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 19:45:12 by agrumbac          #+#    #+#             */
/*   Updated: 2019/01/13 19:25:06 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

bool			cmd_get(int sock, uint64_t body_size)
{
	char			buf[MAXPATHLEN];
	char			*filename;
	void			*file;
	size_t			file_size;
	ssize_t			ret;

	if (body_size >= MAXPATHLEN)
		return (cmd_bad(sock, ERR_TAMPERING_DETECTED));
	ret = recv(sock, buf, body_size, 0);
	if (ret <= 0)
		return (false);
	buf[ret] = '\0';
	filename = simplify_path(buf);
	if (filename == NULL)
		return (cmd_bad(sock, ERR_INVALID_FILENAME));
	file = read_file(filename, &file_size);
	if (file == NULL)
		return (cmd_bad(sock, ERR_GET_FILE));
	if (send_answer(sock, ASW_OK, file_size, file) == false)
	{
		free_file(file, file_size);
		return (false);
	}
	free_file(file, file_size);
	return (true);
}
