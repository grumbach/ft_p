/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_cmd_get.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 19:45:12 by agrumbac          #+#    #+#             */
/*   Updated: 2018/11/20 23:26:20 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static char		*get_filename(char *filename)
{
	/*

	// TODO uncomment when gnebie is done with simplify_path

	filename = simplify_path(filename);
	if (filename == NULL)
		return(cmd_bad(sock, ERR_PERMISSION)); // carefull about type

	*/

	filename = ft_strstr(filename, "get");
	if (filename == NULL)
		return (NULL);

	filename = filename + 3; //skip "get"
	if (filename_invalid(filename))
		return (NULL);

	while (*filename == ' ') //skip all spaces
		filename++;

	return (filename);
}

bool			cmd_get(int sock, uint64_t body_size)
{
	char			buf[MAXPATHLEN];
	char			*filename;
	void			*file;
	size_t			file_size;
	ssize_t			ret;

	if (body_size > MAXPATHLEN)
		return(cmd_bad(sock, ERR_PATHLEN_OVERFLOW));

	if (body_size > 0)
	{
		ret = recv(sock, buf, body_size, 0);
		if (ret == 0)
			return (false);
	}

	filename = get_filename(buf);
	if (filename == NULL)
		return (cmd_bad(sock, ERR_INVALID_FILENAME));

	//send file

	file = read_file(filename, &file_size);
	if (file == NULL)
		return (cmd_bad(sock, ERR_GET_FILE));
	send_answer(sock, ASW_OK, file_size);
	send(sock, file, file_size, 0);
	free_file(file, file_size);

	return (true);
}
