/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_cmd_pwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 18:45:53 by agrumbac          #+#    #+#             */
/*   Updated: 2018/11/18 19:49:22 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

bool			cmd_pwd(int sock, __unused uint64_t body_size)
{
	char			buf[MAXPATHLEN + 1];
	t_ftp_header	request;

	if (!getcwd(buf, MAXPATHLEN))
		return(cmd_bad(sock, 1));
	request.body_size = MAXPATHLEN;
	request.type = ASW_OK;
	send(sock, &(request.type), sizeof(request.type), 0);
	send(sock, buf, MAXPATHLEN, 0);
	return (false);
}
