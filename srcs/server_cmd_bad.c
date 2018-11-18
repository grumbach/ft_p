/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_cmd_bad.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 19:44:48 by agrumbac          #+#    #+#             */
/*   Updated: 2018/11/18 20:53:15 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static const char *g_server_errors[] =
{
	[ERR_BAD_CMD_CODE] = "Bad command code",
	[ERR_CWD] = "Hmassonn what happened?"
};

bool			cmd_bad(int sock, uint64_t body_size)
{
	t_ftp_header	answer;
	size_t			error_len;

	error_len = ft_strlen(g_server_errors[body_size] + 1);
	answer.type = ASW_BAD;
	answer.body_size = error_len;

	send(sock, &answer, sizeof(answer), 0);

	send(sock, g_server_errors[body_size], error_len, 0);

	return (true);
}
