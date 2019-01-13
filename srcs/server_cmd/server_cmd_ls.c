/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_cmd_ls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 19:45:19 by agrumbac          #+#    #+#             */
/*   Updated: 2019/01/13 19:22:54 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include <sys/stat.h>
#include <dirent.h>

#define BUFSIZE 127

static bool		buffered_send(int sock, const char *data, size_t length)
{
	static char				buffer[BUFSIZE + 1];
	static size_t			offset = 0;

	if (!data)
	{
		if (send_answer(sock, ASW_OK, offset, buffer) == false)
			return (false);
		offset = 0;
		return (true);
	}
	while (length >= BUFSIZE - offset)
	{
		ft_memcpy(&buffer[offset], data, BUFSIZE - offset);
		if (send_answer(sock, ASW_MORE, BUFSIZE, buffer) == false)
			return (false);
		length -= BUFSIZE - offset;
		offset = 0;
	}
	ft_memcpy(&buffer[offset], data, length);
	offset += length;
	buffer[offset++] = '\n';
	return (true);
}

static bool		launch_ls(int sock, const char *real_path, const char *path)
{
	struct stat		file_stat;
	void			*dir;
	struct dirent	*file;

	if (lstat(real_path, &file_stat) == -1)
		return (cmd_bad(sock, ERR_PERMISSION));
	if (file_stat.st_mode & S_IFDIR)
	{
		if ((dir = opendir(real_path)) == NULL)
			return (0);
		while ((file = readdir(dir)))
			if (buffered_send(sock, file->d_name, ft_strlen(file->d_name)) \
				== false)
				return (false);
		closedir(dir);
	}
	else if (buffered_send(sock, path, ft_strlen(path)) == false)
		return (false);
	return (buffered_send(sock, NULL, 0));
}

bool			cmd_ls(int sock, uint64_t body_size)
{
	char			path[MAXPATHLEN];
	char			real_path[MAXPATHLEN];
	size_t			ret;

	if (body_size >= MAXPATHLEN)
		return (cmd_bad(sock, ERR_TAMPERING_DETECTED));
	ret = recv(sock, path, body_size, 0);
	if (ret <= 0)
		return (false);
	path[ret] = '\0';
	if (*path == '\0')
		ft_strcpy(path, ".");
	ft_strncpy(real_path, path, MAXPATHLEN);
	if (simplify_path(real_path) == NULL)
		return (cmd_bad(sock, ERR_PERMISSION));
	return (launch_ls(sock, real_path, path));
}
