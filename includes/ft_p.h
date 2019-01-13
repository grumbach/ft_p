/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 17:03:32 by agrumbac          #+#    #+#             */
/*   Updated: 2019/01/13 23:41:40 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_P_H
# define FT_P_H

# define FTP_MAX_QUEUE			5
# define FTP_RECV_BUFFER		0x1000
# define FTP_SEND_BUFFER		0x100000

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
	CMD_BAD,
	CMD_LS,
	CMD_MKDIR,
	CMD_CD,
	CMD_GET,
	CMD_PUT,
	CMD_PWD,
	CMD_QUIT
};

enum			e_answer
{
	ASW_BAD,
	ASW_OK,
	ASW_MORE
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

/*
** socket and network io
*/

int				socket_init(char *address, int port, enum e_mode is_server);
void			socket_cleanup(void);

bool			send_request(int sock, const int type, \
				const size_t body_size, const char *const body);
bool			send_answer(int sock, const int type, \
				const size_t body_size, const char *const body);
bool			receive_answer(int sock, t_ftp_header *answer);
bool			receive_file(int sock, const char *filename, size_t body_size);

/*
** file io
*/

void			*read_file(const char *filename, size_t *file_size);
void			free_file(void *file, size_t file_size);

/*
** basic parsing
*/

bool			parse_args(int ac, char **av, char **address, uint16_t *port);
char			*get_filename_from(char *client_input);

/*
** error announcement
*/

void			fatal(const char *error) __attribute__((cold));
void			warn(const char *warning);

#endif
