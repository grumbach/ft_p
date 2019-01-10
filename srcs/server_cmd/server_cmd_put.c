/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_cmd_put.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 18:45:53 by agrumbac          #+#    #+#             */
/*   Updated: 2019/01/10 17:45:47 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

bool			cmd_put(int sock, uint64_t body_size)
{
	char			filename[MAXPATHLEN];
	t_ftp_header	request;
	ssize_t			ret;

	if (body_size > MAXPATHLEN)
		return(cmd_bad(sock, ERR_PATHLEN_OVERFLOW));

	if ((ret = recv(sock, filename, body_size, 0) <= 0)
	|| (ret = recv(sock, &request, sizeof(request), 0)) <= 0)
		return (false);

	return (receive_file(sock, filename, request.body_size));
}
