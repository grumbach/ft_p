/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_cmd_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 19:45:08 by agrumbac          #+#    #+#             */
/*   Updated: 2018/11/20 18:46:22 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

bool			cmd_cd(int sock, uint64_t body_size)
{
	char			buf[MAXPATHLEN];
	int				ret;

	if (body_size > MAXPATHLEN)
		return(cmd_bad(sock, ERR_PATHLEN_OVERFLOW));

	if (body_size > 0)
	{
		ret = recv(sock, buf, body_size, 0);
		if (ret == 0)
			return (false);
	}
	/*

	// TODO uncomment when gnebie is done with simplify_path

	if (ft_strstr("cd") == NULL)
		return (cmd_bad(sock, ERR_BAD_CMD_CODE));

	char *path = ft_strstr("cd") + 2; //find cd and skip it

	path = simplify_path(path);
	if (path == NULL)
		return(cmd_bad(sock, ERR_PERMISSION));

	ret = chdir(path);

	free(path);
	if (ret == -1)
		return(cmd_bad(sock, ERR_CHDIR));

	*/
	// NB THIS IS TMP
	return (cmd_bad(sock, ERR_PERMISSION));
	// NB THIS IS TMP

	send_answer(sock, ASW_OK, 0);

	return (true);
}
