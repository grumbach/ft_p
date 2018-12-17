/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_cmd_put.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 18:45:53 by agrumbac          #+#    #+#             */
/*   Updated: 2018/12/17 07:16:34 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

bool			cmd_put(__unused int sock, __unused uint64_t body_size)
{
	char			filename[MAXPATHLEN];
	t_ftp_header	request;
	ssize_t			ret;

	if ((ret = recv(sock, filename, body_size, 0) <= 0)
	|| (ret = recv(sock, &request, sizeof(request), 0)) <= 0)
		return (false);

	return (recieve_file(sock, filename, request.body_size));
}
