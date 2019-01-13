/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_io.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 15:29:31 by agrumbac          #+#    #+#             */
/*   Updated: 2019/01/13 19:08:30 by agrumbac         ###   ########.fr       */
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
**
** filename_invalid:
** - checks if filename is empty or not printable
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
