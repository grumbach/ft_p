/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_cmd_get.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 19:45:12 by agrumbac          #+#    #+#             */
/*   Updated: 2018/11/20 18:54:12 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

bool			cmd_get(int sock, uint64_t body_size)
{
	char			buf[MAXPATHLEN];
	char			*filename;
	void			*file;
	size_t			file_size;
	int				ret;

	if (body_size > MAXPATHLEN)
		return(cmd_bad(sock, ERR_PATHLEN_OVERFLOW));

	if (body_size > 0)
	{
		ret = recv(sock, buf, body_size, 0);
		if (ret == 0)
			return (false);
	}

	filename = ft_strstr(buf, "get");
	if (filename == NULL)
		return (cmd_bad(sock, ERR_BAD_CMD_CODE));
	filename = filename + 3; //skip "get"
	if (filename_invalid(filename))
		return (cmd_bad(sock, ERR_INVALID_FILENAME));

	//send file
	file = read_file(filename, &file_size);
	if (file == NULL)
		return (cmd_bad(sock, ERR_GET_FILE));
	send_answer(sock, ASW_OK, body_size);
	send(sock, file, file_size, 0);
	free_file(file, file_size);

	return (true);
}
