/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_cmd_bad.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 19:44:48 by agrumbac          #+#    #+#             */
/*   Updated: 2018/12/16 23:28:27 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

#define STRLEN(s)	(sizeof(s)/sizeof(s[0]))

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

static const size_t g_server_errors_len[] =
{
	[ERR_BAD_CMD_CODE] = STRLEN(g_server_errors[ERR_BAD_CMD_CODE]),
	[ERR_CWD] = STRLEN(g_server_errors[ERR_CWD]),
	[ERR_PATHLEN_OVERFLOW] = STRLEN(g_server_errors[ERR_PATHLEN_OVERFLOW]),
	[ERR_CHDIR] = STRLEN(g_server_errors[ERR_CHDIR]),
	[ERR_PERMISSION] = STRLEN(g_server_errors[ERR_PERMISSION]),
	[ERR_GET_FILE] = STRLEN(g_server_errors[ERR_GET_FILE]),
	[ERR_INVALID_FILENAME] = STRLEN(g_server_errors[ERR_INVALID_FILENAME])
};

bool			cmd_bad(int sock, uint64_t body_size)
{
	const size_t	error_len = g_server_errors_len[body_size];

	send_answer(sock, ASW_BAD, error_len);
	send(sock, g_server_errors[body_size], error_len, 0);
	return (true);
}
