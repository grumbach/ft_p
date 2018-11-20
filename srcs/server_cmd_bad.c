/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_cmd_bad.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 19:44:48 by agrumbac          #+#    #+#             */
/*   Updated: 2018/11/20 15:58:05 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static const char *g_server_errors[] =
{
	[ERR_BAD_CMD_CODE] = "bad command code",
	[ERR_CWD] = "cwd failed",
	[ERR_PATHLEN_OVERFLOW] = "MAXPATHLEN exeeded",
	[ERR_CHDIR] = "chdir failed",
	[ERR_PERMISSION] = "permission denied",
	[ERR_GET_FILE] = "failed to get file",
	[ERR_INVALID_FILENAME] = "invalid filename"
};

bool			cmd_bad(int sock, uint64_t body_size)
{
	t_ftp_header	answer;
	size_t			error_len;

	if (body_size >= ERR_LAST)
		body_size = 0;

	error_len = ft_strlen(g_server_errors[body_size]) + 1;
	answer.type = ASW_BAD;
	answer.body_size = error_len;

	send(sock, &answer, sizeof(answer), 0);

	send(sock, g_server_errors[body_size], error_len, 0);

	return (true);
}
