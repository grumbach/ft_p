/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_cmd_pwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 18:45:53 by agrumbac          #+#    #+#             */
/*   Updated: 2018/11/20 23:26:53 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

bool			cmd_pwd(int sock, __unused uint64_t body_size)
{
	char			path[MAXPATHLEN];
	size_t			path_len;

	if (getcwd(path, MAXPATHLEN) == NULL)
		return(cmd_bad(sock, ERR_CWD));
	path_len = ft_strlen(path) + 1;

	send_answer(sock, ASW_OK, path_len);

	send(sock, path, path_len, 0);

	return (true);
}
