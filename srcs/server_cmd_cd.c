/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_cmd_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 19:45:08 by agrumbac          #+#    #+#             */
/*   Updated: 2018/11/20 23:40:15 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static char		*get_path_from(const char *buf)
{
	char		*path;

	path = ft_strstr(buf, "cd");
	if (path == NULL)
		return (NULL);

	path = path + 2; //find cd and skip it
	while (*path == ' ')//trim white spaces
		path++;

	// TODO uncomment when gnebie is done with simplify_path
	/*
	path = simplify_path(path);
	if (path == NULL)
		return(cmd_bad(sock, ERR_PERMISSION));
	*/
	return (path);
}

bool			cmd_cd(int sock, uint64_t body_size)
{
	char			buf[MAXPATHLEN];
	ssize_t			ret;
	char			*path;

	if (body_size > MAXPATHLEN)
		return(cmd_bad(sock, ERR_PATHLEN_OVERFLOW));

	if (body_size > 0)
	{
		ret = recv(sock, buf, body_size, 0);
		if (ret == 0)
			return (false);
	}

	path = get_path_from(buf);
	if (path == NULL)
		return (cmd_bad(sock, ERR_PERMISSION));

	ret = chdir(path);

	// free(path); //gnebie!
	if (ret == -1)
		return(cmd_bad(sock, ERR_CHDIR));

	send_answer(sock, ASW_OK, 0);

	return (true);
}
