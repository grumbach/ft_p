/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_cmd_bad.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 19:44:48 by agrumbac          #+#    #+#             */
/*   Updated: 2018/12/17 05:53:49 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

# define STR_BAD_CMD_CODE			"bad command code"
# define STR_CWD					"cwd failed"
# define STR_PATHLEN_OVERFLOW		"MAXPATHLEN exeeded"
# define STR_CHDIR					"chdir failed"
# define STR_PERMISSION				"permission denied"
# define STR_GET_FILE				"failed to get file"
# define STR_INVALID_FILENAME		"invalid filename"

static const char	*g_server_errors[] =
{
	[ERR_BAD_CMD_CODE] = STR_BAD_CMD_CODE,
	[ERR_CWD] = STR_CWD,
	[ERR_PATHLEN_OVERFLOW] = STR_PATHLEN_OVERFLOW,
	[ERR_CHDIR] = STR_CHDIR,
	[ERR_PERMISSION] = STR_PERMISSION,
	[ERR_GET_FILE] = STR_GET_FILE,
	[ERR_INVALID_FILENAME] = STR_INVALID_FILENAME
};

static const size_t	g_server_errors_len[] =
{
	[ERR_BAD_CMD_CODE] = sizeof(STR_BAD_CMD_CODE),
	[ERR_CWD] = sizeof(STR_CWD),
	[ERR_PATHLEN_OVERFLOW] = sizeof(STR_PATHLEN_OVERFLOW),
	[ERR_CHDIR] = sizeof(STR_CHDIR),
	[ERR_PERMISSION] = sizeof(STR_PERMISSION),
	[ERR_GET_FILE] = sizeof(STR_GET_FILE),
	[ERR_INVALID_FILENAME] = sizeof(STR_INVALID_FILENAME)
};

/*
** cmd_bad
** - this function is ONLY called internally so body_size should always be
**   a macro starting with ERR_...
*/

bool				cmd_bad(int sock, uint64_t body_size)
{
	const size_t	error_len = g_server_errors_len[body_size];

	send_answer(sock, ASW_BAD, error_len);
	send(sock, g_server_errors[body_size], error_len, 0);
	return (true);
}
