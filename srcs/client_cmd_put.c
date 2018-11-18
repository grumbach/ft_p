/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_cmd_put.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 18:45:55 by agrumbac          #+#    #+#             */
/*   Updated: 2018/11/18 19:50:26 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

// static void			*g_file_content = NULL;
// static size_t		g_filesize;
//
// static bool				read_file(const char *filename)
// {
// 	int				fd;
// 	void			*ptr;
// 	struct stat		buf;
//
// 	if ((fd = open(filename, O_RDONLY)) < 0)
// 		return (manage_error(0, "no such file or directory"));
// 	if (fstat(fd, &buf) < 0)
// 		return (manage_error(1, "fstat failed"));
// 	if (buf.st_mode & S_IFDIR)
// 		return (manage_error(1, "can't send directories"));
// 	if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
// 		return (manage_error(0, "mmap failed"));
// 	if (close(fd))
// 		return (manage_error(0, "close failed"));
//
// 	g_file_content = ptr;
// 	g_filesize = buf.st_size;
// 	return(true);
// }
//
// static bool				free_file(void)
// {
// 	if (munmap(g_file_content, g_filesize))
// 		return (manage_error(0, "munmap failed"));
// 	return (true);
// }

//TODO protect all send and recv monkey business

bool			cmd_put(int sock, char *client_input)
{
	// t_ftp_header	request;
	// char			*filename;
	//
	// filename = ft_strlaststr(client_input, "/");
	// if (filename == NULL)
	// 	filename = client_input + 3;//TODO DANGER +3!!
	//
	// if (!read_file(filename))
	// 	return (c_est_la_merde(0));//"error was printed already") | true);
	//
	// // sending filename + '\0' + file_content
	// request.body_size = ft_strlen(filename) + 1 + g_filesize;
	// request.type = CMD_PUT;
	//
	// //send header
	// send(sock, &request, sizeof(request), 0);
	//
	// //send data
	// send(sock, filename, ft_strlen(filename) + 1, 0);
	// send(sock, g_file_content, g_filesize, 0);
	//
	// free_file();
	// return (true);
}
