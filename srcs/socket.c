/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 20:18:32 by agrumbac          #+#    #+#             */
/*   Updated: 2018/11/18 18:45:03 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

static int		g_sock;

/*
** ----------------------------- server and client -----------------------------
*/

static void		client_init(struct sockaddr_in *sockaddr)
{
	if (connect(g_sock, (struct sockaddr *)sockaddr , sizeof(*sockaddr)) < 0)
		fatal("failed to connect");
}

static void		server_init(struct sockaddr_in *sockaddr)
{
	if (bind(g_sock, (struct sockaddr *)sockaddr , sizeof(*sockaddr)) < 0)
		fatal("failed to bind socket");

	listen(g_sock, FTP_MAX_QUEUE);
}

/*
** -----------------------------------------------------------------------------
*/

int				socket_init(char *address, int port, enum e_mode is_server)
{
	struct sockaddr_in	sockaddr;
	static void			(*init_helper[2])(struct sockaddr_in *) =
	{
		client_init,
		server_init
	};

	g_sock = socket(PF_INET , SOCK_STREAM , 0);

	if (g_sock == -1)
		fatal("failed to create socket");

	//for faster server relaunch
	if (setsockopt(g_sock, SOL_SOCKET, SO_REUSEADDR, &(int){ 1 }, sizeof(int)) < 0)
		fatal("failed to setsockopt(SO_REUSEADDR)");

	sockaddr.sin_family = PF_INET;
	sockaddr.sin_addr.s_addr = address ? inet_addr(address) : INADDR_ANY;
	sockaddr.sin_port = htons(port);

	init_helper[is_server](&sockaddr);

	return (g_sock);
}

void			socket_cleanup(void)
{
	close(g_sock);
}
