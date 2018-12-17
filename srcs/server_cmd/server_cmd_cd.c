/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_cmd_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 19:45:08 by agrumbac          #+#    #+#             */
/*   Updated: 2018/12/17 02:21:36 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

bool			cmd_cd(int sock, uint64_t body_size)
{
	char			buf[MAXPATHLEN];
	ssize_t			ret;
	char			*path;

	if (body_size > MAXPATHLEN)
		return(cmd_bad(sock, ERR_PATHLEN_OVERFLOW));

	if (body_size > 0)//TODO test for recv(sock, buf, 0, 0)
	{
		ret = recv(sock, buf, body_size, 0);
		if (ret == 0)
			return (false);
	}

	path = simplify_path(buf);

	ret = chdir(path);

	free(path); /*TODO rm this after issue#5 [FIX] gnebie! */

	if (ret == -1)
		return(cmd_bad(sock, ERR_CHDIR));

	send_answer(sock, ASW_OK, 0);

	return (true);
}
