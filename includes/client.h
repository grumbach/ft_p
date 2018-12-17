/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 18:12:17 by agrumbac          #+#    #+#             */
/*   Updated: 2018/12/17 05:56:57 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# include "ft_p.h"

int				lexer(const char * client_input, char **input_arg);

/*
** Client commands
*/

bool			cmd_bad(int sock, char *client_input);
bool			cmd_ls(int sock, char *client_input);
bool			cmd_mkdir(int sock, char *client_input);
bool			cmd_cd(int sock, char *client_input);
bool			cmd_get(int sock, char *client_input);
bool			cmd_quit(int sock, char *client_input);
bool			cmd_put(int sock, char *client_input);
bool			cmd_pwd(int sock, char *client_input);

#endif
