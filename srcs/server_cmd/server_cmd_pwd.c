/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_cmd_pwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 18:45:53 by agrumbac          #+#    #+#             */
/*   Updated: 2019/01/11 20:47:37 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

bool			cmd_pwd(int sock, __unused uint64_t body_size)
{
	char			path[MAXPATHLEN];
	char			*user_path;
	size_t			path_len;
	size_t			root_len;

	if (getcwd(path, MAXPATHLEN) == NULL)
		return(cmd_bad(sock, ERR_CWD));
	path_len = ft_strlen(path) + 1;
	root_len = root_path_len();

	if (path_len < root_len)
		return(cmd_bad(sock, ERR_TAMPERING_DETECTED));

	path_len = path_len - root_len;
	user_path = path + root_len;

	if (*user_path == '\0')
		ft_strcpy(user_path, "/");

	send_answer(sock, ASW_OK, path_len);

	send(sock, user_path, path_len, 0);

	return (true);
}
