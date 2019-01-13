/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_io.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 15:29:31 by agrumbac          #+#    #+#             */
/*   Updated: 2019/01/13 23:44:57 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"
#include <sys/stat.h>

/*
** read_file:
** - writes file size into file_size
** - returns ptr to allocated data
** - returns NULL when something goes wrong
**
** free_file:
** - unmaps file from memory
*/

void		*read_file(const char *filename, size_t *file_size)
{
	int				fd;
	void			*ptr;
	struct stat		buf;

	if (((fd = open(filename, O_RDONLY)) < 0)
	|| (fstat(fd, &buf) < 0)
	|| (buf.st_mode & S_IFDIR)
	|| ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) \
		== MAP_FAILED)
	|| (close(fd)))
		return (NULL);
	*file_size = buf.st_size;
	return (ptr);
}

void		free_file(void *file, size_t file_size)
{
	munmap(file, file_size);
}

bool		receive_file(int sock, const char *filename, size_t body_size)
{
	char		buf[FTP_RECV_BUFFER];
	int			fd;
	ssize_t		ret;

	if ((fd = open(filename, O_CREAT | O_WRONLY, 0700)) < 0)
	{
		warn("failed to open file for writing");
		return (true);
	}
	while (body_size > 0)
	{
		ret = recv(sock, buf, FTP_RECV_BUFFER, 0);
		if (ret == -1)
			warn("failed to receive file content");
		if (ret <= 0)
		{
			close(fd);
			return (false);
		}
		if (write(fd, buf, ret) == -1)
			return (true);
		body_size -= ret;
	}
	close(fd);
	return (true);
}
