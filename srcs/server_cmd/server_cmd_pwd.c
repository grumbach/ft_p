/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_cmd_pwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 18:45:53 by agrumbac          #+#    #+#             */
/*   Updated: 2019/01/13 19:23:26 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

bool			cmd_pwd(int sock, uint64_t body_size)
{
	char			path[MAXPATHLEN];
	char			*user_path;
	size_t			path_len;
	size_t			root_len;

	(void)body_size;
	if (getcwd(path, MAXPATHLEN) == NULL)
		return (cmd_bad(sock, ERR_CWD));
	path_len = ft_strlen(path) + 1;
	root_len = root_path_len();
	if (path_len < root_len)
		return (cmd_bad(sock, ERR_TAMPERING_DETECTED));
	path_len = path_len - root_len;
	user_path = path + root_len;
	if (*user_path == '\0')
		ft_strcpy(user_path, "/");
	return (send_answer(sock, ASW_OK, path_len, user_path));
}
