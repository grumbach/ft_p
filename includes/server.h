/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 18:10:58 by agrumbac          #+#    #+#             */
/*   Updated: 2018/11/18 20:17:19 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include "ft_p.h"

void			no_return_child_code(int client_sock);

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
