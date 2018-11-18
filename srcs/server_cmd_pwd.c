/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_cmd_pwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 18:45:53 by agrumbac          #+#    #+#             */
/*   Updated: 2018/11/18 19:49:22 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

bool			cmd_pwd(int sock, uint64_t body_size)
{
	// char			buf[FTP_BODY_BUFFER];
	// t_ftp_header	request;
	//
	//
	// if (!getcwd(buf, FTP_BODY_BUFFER))
	// 	return(manage_error("pwd too long"));
	//
	// request.body_size = ft_strlen(filename) + 1 + g_filesize;
	// request.type = ASW_OK;
	// send(sock, &request, sizeof(request), 0);
	//
	// send(sock, buf, FTP_BODY_BUFFER, 0);
	//
	// return (false);
}
