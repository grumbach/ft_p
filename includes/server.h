/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 18:10:58 by agrumbac          #+#    #+#             */
/*   Updated: 2019/01/13 17:28:51 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include "ft_p.h"

void			no_return_child_code(int client_sock) __attribute__((noreturn));

/*
** Server side path checking
*/

bool			set_root_path(void);
size_t			root_path_len(void);
char			*simplify_path(char *path);

/*
** Server error codes
*/

enum			e_server_errors
{
	ERR_BAD_CMD_CODE,
	ERR_CWD,
	ERR_TAMPERING_DETECTED,
	ERR_CHDIR,
	ERR_PERMISSION,
	ERR_GET_FILE,
	ERR_INVALID_FILENAME
};

/*
** Server commands
*/

bool			cmd_bad(int sock, uint64_t body_size);
bool			cmd_ls(int sock, uint64_t body_size);
bool			cmd_mkdir(int sock, uint64_t body_size);
bool			cmd_cd(int sock, uint64_t body_size);
bool			cmd_get(int sock, uint64_t body_size);
bool			cmd_put(int sock, uint64_t body_size);
bool			cmd_pwd(int sock, uint64_t body_size);

#endif
