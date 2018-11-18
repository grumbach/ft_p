/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_cmd_bad.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 19:44:48 by agrumbac          #+#    #+#             */
/*   Updated: 2018/11/18 19:54:00 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

bool			cmd_bad(int sock, uint64_t body_size)
{
	ft_printf("cmd_bad");
}
//{send(CMD_BAD, error.len); send(error)}
