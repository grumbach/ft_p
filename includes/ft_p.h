/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 17:03:32 by agrumbac          #+#    #+#             */
/*   Updated: 2018/11/02 22:40:27 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_P_H
# define FT_P_H

# define FTP_MAX_USERS			42

# include "libft.h"
# include <sys/socket.h>
# include <arpa/inet.h>

enum			e_mode
{
	CLIENT,
	SERVER
};

int				socket_init(char *address, int port, enum e_mode is_server);
void			socket_cleanup(int sock);

void			fatal(const char *error);

#endif
