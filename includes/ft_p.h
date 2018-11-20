/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 17:03:32 by agrumbac          #+#    #+#             */
/*   Updated: 2018/11/20 18:55:04 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_P_H
# define FT_P_H

# define FTP_MAX_QUEUE			5
# define FTP_CLIENT_MAX_INPUT	2048
# define FTP_RECV_BUFFER		1024

# include "libft.h"
# include <arpa/inet.h>
# include <sys/socket.h>
# include <sys/param.h>
# include <sys/mman.h>
# include <stdbool.h>
# include <fcntl.h>

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

void			send_request(int sock, const int type, const size_t body_size);
void			send_answer(int sock, const int type, const size_t body_size);
bool			recieve_error(int sock, size_t message_len);
bool			recieve_answer(int sock, t_ftp_header *answer);

void			*read_file(const char *filename, size_t *file_size);
void			free_file(void *file, size_t file_size);
bool			filename_invalid(const char *filename);

void			fatal(const char *error);
void			warn(const char *warning);

#endif
