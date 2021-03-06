/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_cmd_pwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 18:45:55 by agrumbac          #+#    #+#             */
/*   Updated: 2019/01/12 18:52:10 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

__attribute__((warn_unused_result))
bool			cmd_pwd(int sock, __unused char *client_input)
{
	char			path[MAXPATHLEN];
	t_ftp_header	answer;
	ssize_t			ret;

	if (send_request(sock, CMD_PWD, 0, NULL) == false)
		return (false);

	if (receive_answer(sock, &answer) == false)
		return (false);

	if (answer.type != ASW_OK || answer.body_size >= MAXPATHLEN)
		return (true);

	ret = recv(sock, path, answer.body_size, 0);
	if (ret == 0)
		return (false);
	if (ret == -1)
	{
		warn("failed to receive path from server");
		return (false);
	}

	path[ret] = '\0';
	ft_puts(path);

	return (true);
}
