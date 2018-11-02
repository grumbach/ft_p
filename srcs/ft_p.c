/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 20:18:32 by agrumbac          #+#    #+#             */
/*   Updated: 2018/11/02 23:16:06 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

void			fatal(const char *error)
{
	//OMG 3 SYSCALLS!
	ft_perr("Fatal: ");
	ft_perr(error);
	ft_perr("\n");
	exit(-1);
}

/*
** ----------------------------- server and client -----------------------------
*/

static void		client_init(int sock, struct sockaddr_in *sockaddr)
{
	if (connect(sock, (struct sockaddr *)sockaddr , sizeof(*sockaddr)) < 0)
		fatal("Failed to connect");
}

static void		server_init(int sock, struct sockaddr_in *sockaddr)
{
	if (bind(sock, (struct sockaddr *)sockaddr , sizeof(*sockaddr)) < 0)
		fatal("Failed to bind socket");

	listen(sock, FTP_MAX_USERS);
}

/*
** -----------------------------------------------------------------------------
*/

int				socket_init(char *address, int port, enum e_mode is_server)
{
	int					sock;
	struct sockaddr_in	sockaddr;
	static void			(*init_helper[2])(int, struct sockaddr_in *) =
	{
		client_init,
		server_init
	};

	sock = socket(PF_INET , SOCK_STREAM , 0);

	// if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &(int){ 1 }, sizeof(int)) < 0)
	// 	fatal("Failed to setsockopt(SO_REUSEADDR)");

	if (sock == -1)
		fatal("Failed to create socket");

	sockaddr.sin_family = PF_INET;
	sockaddr.sin_addr.s_addr = address ? inet_addr(address) : INADDR_ANY;
	sockaddr.sin_port = htons(port);

	init_helper[is_server](sock, &sockaddr);

	return (sock);
}

void			socket_cleanup(int sock)
{
	close(sock);
}
