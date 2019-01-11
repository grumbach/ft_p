/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_cmd_ls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 19:45:19 by agrumbac          #+#    #+#             */
/*   Updated: 2019/01/11 16:38:44 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include <sys/stat.h>
#include <dirent.h>

#define BUFSIZE 127

void		buffered_send(int sock, const char *data, size_t length)
{
	static char				buffer[BUFSIZE + 1];
	static size_t			offset = 0;

	// flush case
	if (!data)
	{
		send_full_answer(sock, ASW_OK, buffer, offset);
		offset = 0;
		return ;
	}
	while (length >= BUFSIZE - offset)
	{
		ft_memcpy(&buffer[offset], data, BUFSIZE - offset);
		send_full_answer(sock, ASW_MORE, buffer, BUFSIZE);
		length -= BUFSIZE - offset;
		offset = 0;
	}
	ft_memcpy(&buffer[offset], data, length);
	offset += length;
	buffer[offset++] = '\n';
}

bool		launch_ls(int sock, const char *real_path, const char *path)
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
			buffered_send(sock, file->d_name, ft_strlen(file->d_name));
		closedir(dir);
	}
	else
		buffered_send(sock, path, ft_strlen(path));
	buffered_send(sock, NULL, 0);
	return (true);
}

bool			cmd_ls(int sock, uint64_t body_size)
{
	char			path[MAXPATHLEN + 1];
	char			*real_path;

	if (body_size > MAXPATHLEN)
		return (cmd_bad(sock, ERR_PATHLEN_OVERFLOW));
	if (recv(sock, path, body_size, 0) == 0)
		return (false);
	if (*path == '\0')
		ft_strcpy(path, ".");

	real_path = simplify_path(path);
	if (real_path == NULL)
		return (cmd_bad(sock, ERR_PERMISSION));

	launch_ls(sock, real_path, path);

	return (true);
}
