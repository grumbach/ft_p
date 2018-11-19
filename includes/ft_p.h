/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 17:03:32 by agrumbac          #+#    #+#             */
/*   Updated: 2018/11/16 16:50:51 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_P_H
# define FT_P_H

# define FTP_MAX_QUEUE			5
# define FTP_CLIENT_MAX_INPUT	2048

# include "libft.h"
# include <sys/socket.h>
# include <arpa/inet.h>
# include <stdbool.h>

enum			e_mode
{
	CLIENT,
	SERVER
};

enum			e_cmd
{
	CMD_BAD,    /* for any invalid commands */
	CMD_LS,     /* list in the current server’s directory */
	CMD_MKDIR,  /* make a directory */
	CMD_CD,     /* change the current server’s directory */
	CMD_GET,    /* download the file file from the server to the client */
	CMD_PUT,    /* upload the file file from the client to the server */
	CMD_PWD,    /* display the path of the current server’s directory */
	CMD_QUIT,   /* cuts the connection + exit the program */
	CMD_LAST    /* number of CMDs */
};

enum			e_answer
{
	ASW_BAD,    /* for any invalid commands */
	ASW_OK,     /* success answer */
	ASW_MORE,   /* if there is more data to read */
	ASW_LAST    /* number of ASWs */
};

/*
** ----------------------------- Homemade Protocol -----------------------------
** while connected:
**     client sends [t_ftp_header] [body]
**     server sends [t_ftp_header] [body]
*/

typedef struct	s_ftp_header
{
	uint64_t	body_size;
	uint32_t	type;
}				t_ftp_header;

/*
** -----------------------------------------------------------------------------
*/

bool			parse_args(int ac, char **av, char **address, uint16_t *port);

int				socket_init(char *address, int port, enum e_mode is_server);
void			socket_cleanup(void);

void			fatal(const char *error);
char			*simplify_path(char *path);

#endif
