/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_cmd_pwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 18:45:55 by agrumbac          #+#    #+#             */
/*   Updated: 2018/11/18 19:49:17 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

bool			cmd_pwd(int sock, __unused char *client_input)
{
	t_ftp_header	request;
	char			buf[MAXPATHLEN + 1];

	request.body_size = 0;
	request.type = CMD_PUT;

	//send header
	send(sock, &(request.type), sizeof(request.type), 0);
	recv(sock, &(request.type), sizeof(request.type), 0);
	if (request.type == CMD_BAD)
		ft_printf("error for pwd"); // checker la fonction error_server
	else
	{
		recv(sock, buf, MAXPATHLEN, 0);
		ft_printf("%s\n", buf);
	}
	return (true);
}
