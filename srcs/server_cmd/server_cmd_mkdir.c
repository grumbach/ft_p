/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_cmd_mkdir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 19:43:01 by agrumbac          #+#    #+#             */
/*   Updated: 2019/01/13 19:24:05 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include <sys/types.h>
#include <sys/stat.h>

bool			cmd_mkdir(int sock, uint64_t body_size)
{
	char			buf[MAXPATHLEN];
	ssize_t			ret;
	char			*path;

	if (body_size >= MAXPATHLEN)
		return (cmd_bad(sock, ERR_TAMPERING_DETECTED));
	ret = recv(sock, buf, body_size, 0);
	if (ret <= 0)
		return (false);
	buf[ret] = '\0';
	path = simplify_path(buf);
	if (path == NULL)
		return (cmd_bad(sock, ERR_PERMISSION));
	ret = mkdir(path, S_IRWXU | S_IRGRP | S_IROTH);
	if (ret == -1)
		return (cmd_bad(sock, ERR_CHDIR));
	return (send_answer(sock, ASW_OK, 0, NULL));
}
