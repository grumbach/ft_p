/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_cmd_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 19:45:08 by agrumbac          #+#    #+#             */
/*   Updated: 2019/01/10 18:27:50 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

bool			cmd_cd(int sock, uint64_t body_size)
{
	char			buf[MAXPATHLEN];
	char			*path;

	if (body_size > MAXPATHLEN)
		return(cmd_bad(sock, ERR_TAMPERING_DETECTED));

	if (recv(sock, buf, body_size, 0) == 0)
		return (false);

	if (*buf == '\0')
		ft_strcpy(buf, "/");
	path = simplify_path(buf);
	if (path == NULL)
		return (cmd_bad(sock, ERR_PERMISSION));

	if (chdir(path) == -1)
		return(cmd_bad(sock, ERR_CHDIR));

	send_answer(sock, ASW_OK, 0);
	return (true);
}
