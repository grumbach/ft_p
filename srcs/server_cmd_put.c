/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_cmd_put.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 18:45:53 by agrumbac          #+#    #+#             */
/*   Updated: 2018/11/18 19:49:56 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static ssize_t	read_from_recv(int sock, char *buf)
{
	// ssize_t ret;
	//
	// ret = recv(sock, buf, FTP_BODY_BUFFER, 0);
	// if (ret == -1)
	// 	c_est_la_merde(ASW_BAD);
	// else if (ret == 0)
	// 	return (0); //connection closed
	// return(ret);
}

bool			cmd_put(int sock, uint64_t body_size)
{
	// char		buf[FTP_BODY_BUFFER];
	// int			ret;
	// size_t		read_data;
	// int			fd;
	//
	// ret = read_from_recv(sock, buf); // TODO protect this
	// fd = open(buf, O_WRONLY); // TODO protect this
	// read_data = ft_strlen(buf) + 1;
	// write(fd, buf + read_data, ret - read_data); // TODO protect this
	//
	// while (read_data < body_size)
	// {
	// 	ret = read_from_recv(sock, buf); // TODO protect this
	// 	write(fd, buf, ret); // TODO protect this
	// 	read_data += ret;
	// }
	// close(fd); // TODO protect this (this is a joke)
	// return (false);
}
