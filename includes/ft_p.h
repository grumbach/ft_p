/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 17:03:32 by agrumbac          #+#    #+#             */
/*   Updated: 2019/01/11 19:52:12 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_P_H
# define FT_P_H

# define FTP_MAX_QUEUE			5
# define FTP_RECV_BUFFER		1024

# include "libft.h"
# include <arpa/inet.h>
# include <sys/socket.h>
# include <sys/param.h>
# include <sys/mman.h>
# include <stdbool.h>
# include <fcntl.h>

# define FTP_LOG				"\033[36m[LOG] \033[0m"
# define FTP_WARN				"\033[33m[WARNING] \033[0m"
# define FTP_ERR				"\033[31m[ERROR] \033[0m"
# define FTP_FATAL				"\033[31;5m[FATAL ERROR] \033[0m"

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
	CMD_QUIT    /* cuts the connection + exit the program (must be last) */
};

enum			e_answer
{
	ASW_BAD,    /* for any invalid commands */
	ASW_OK,     /* success answer */
	ASW_MORE    /* if there is more data to read */
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
void			send_full_answer(int sock, const int type, char *body, const ssize_t body_size);
bool			receive_answer(int sock, t_ftp_header *answer);
bool			receive_file(int sock, const char *filename, size_t body_size);

void			*read_file(const char *filename, size_t *file_size);
void			free_file(void *file, size_t file_size);

char			*get_filename_from(char *client_input);
char			*simplify_path(char *path);
size_t			root_path_len(void);

void			fatal(const char *error) __attribute__((cold));
void			warn(const char *warning);

#endif
