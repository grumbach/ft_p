/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_cmd_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 19:45:08 by agrumbac          #+#    #+#             */
/*   Updated: 2018/11/19 00:06:28 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

bool			cmd_cd(int sock, uint64_t body_size)
{
	char			buf[MAXPATHLEN];
	t_ftp_header	answer;
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

	char *path = ft_strstr("cd") + 2; //find cd and skip it

	path = simplify_path(path);
	if (path == NULL)
		return(cmd_bad(sock, ERR_PERMISSION));

	ret = chdir(path);

	free(path);
	if (ret == -1)
		return(cmd_bad(sock, ERR_CHDIR));

	*/

	answer.type = ASW_OK;
	answer.body_size = 0;

	send(sock, &answer, sizeof(answer), 0);
	return (true);
}
